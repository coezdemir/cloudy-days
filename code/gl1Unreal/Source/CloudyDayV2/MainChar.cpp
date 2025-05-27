// Fill out your copyright notice in the Description page of Project Settings
#include "MainChar.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Shockwave.h"
#include "CCProjectile.h"


// Sets default values
AMainChar::AMainChar()
{
	PrimaryActorTick.bCanEverTick = true;
	//Setting up basic attributes and components
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	Muzzle->SetupAttachment(RootComponent);
	Muzzle->SetRelativeLocation(FVector(0.f, 45.f, -5.f));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	FRotator RotationView = FRotator(-20.f, 0.f, 0.f);
	SpringArm->SetRelativeRotation(RotationView);
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringArm->SetupAttachment(GetMesh());
	Camera->SetupAttachment(SpringArm);
	MaxWater = 100.f;
	CurrentWater = 100.f;
	GVScale = 0.f;
	Hovering = false;
	bGrowthChange = false;
	Vincible = true;
	NormalScale = FVector(3.f, 3.f, 3.f);
	SmallestScale = FVector(1.f, 1.f, 1.f);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMainChar::OnHit);
	blinkcount = 0;
}

// Called when the game starts or when spawned
void AMainChar::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Chracter is hovering? Substract water from water depot
	if (Hovering && (CurrentWater - 0.1) > 0) {
		ChangeWaterLevel(-0.15f);
		if (!GVScale == 1.f) { 
			//Letting gravity slowly come back so that hovering is not overpowered
			GVScale = +0.025f;
			GetCharacterMovement()->GravityScale = GVScale;
		}
	}else {
		//Restoring default attributes
		Hovering = false;
		HoverReleased();
	}
	if (bGrowthChange) {
		//Changing actual scale with this function call
		ChangeScale(Growth);
	}
	if (CurrentWater <= 1.f)CleanDestroy();
}

// Called to bind functionality to input
void AMainChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveForward", this, &AMainChar::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMainChar::MoveRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMainChar::MyJump);
	InputComponent->BindAxis("MoveCamUp", this, &AMainChar::MoveCamUp);
	InputComponent->BindAxis("MoveCamRight", this, &AMainChar::MoveCamRight);
	InputComponent->BindAction("Hover", IE_Pressed, this, &AMainChar::HoverPressed);
	InputComponent->BindAction("Hover", IE_Released, this, &AMainChar::HoverReleased);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AMainChar::Shoot);
	InputComponent->BindAction("GroundPound", IE_Pressed, this, &AMainChar::GroundPound);
}

void AMainChar::MoveForward(float Val)
{
	if (Controller && Val)AddMovementInput(GetActorForwardVector(), Val);
}

void AMainChar::MoveRight(float Val)
{
	if (Controller && Val)AddMovementInput(GetActorRightVector(), Val);
}

void AMainChar::MyJump()
{
	if (Controller)Jump();
}


void AMainChar::MoveCamUp(float Val)
{
	if (Controller) SpringArm->AddRelativeRotation(FRotator(Val, 0.f, 0.f));
}


void AMainChar::MoveCamRight(float Val)
{
	//We use AddControllerYawInput to change the orienatation
	if (Controller)AddControllerYawInput(Val);
}

void AMainChar::HoverPressed()
{
	if (Controller && GetCharacterMovement()->IsFalling() && (CurrentWater - 0.1) > 0) {
		//Setting up hovering attributes
		GetCharacterMovement()->GravityScale = GVScale;
		GetCharacterMovement()->Velocity.Z = 0.f;
		Hovering = true;
		//Spawnparams for hover projectile and spawning it
		FActorSpawnParameters ActorSpawnParams;
		const FRotator SpawnRotation = GetControlRotation();
		const FVector SpawnLocation = ((Muzzle != nullptr) ? Muzzle->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(FVector(0.f, 0.f, -100.f));
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		GetWorld()->SpawnActor<AActor>(ProjectileHoverClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
}

void AMainChar::HoverReleased()
{
	if (Controller) {
		Hovering = false;
		GetCharacterMovement()->GravityScale = 1.f;
	}
}

void AMainChar::Shoot()
{
	if (Controller && (CurrentWater - 2.5) > 0) {
		ChangeWaterLevel(-2.5f);
		//Setting up spawn parameters
		FActorSpawnParameters ActorSpawnParams;
		const FRotator SpawnRotation = GetControlRotation();
		const FVector SpawnLocation = ((Muzzle != nullptr) ? Muzzle->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(FVector(100.f, 0.f, 0.f));
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		//Actual spawning happens here
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
}

void AMainChar::GroundPound()
{
	if (Controller && GetCharacterMovement()->IsFalling() && (CurrentWater - 2.5f) > 0) {
		ChangeWaterLevel(-5.f);
		GetCharacterMovement()->AddForce(FVector(0.f, 0.f, -20000000.f));
		Vincible = false;
		GetWorldTimerManager().SetTimer(VincibilityHandle, this, &AMainChar::MakeVincible, 0.5f, false);
		GP = true;
	}

}

void AMainChar::SpawnGroundPoundCollision()
{
	FVector Location = GetActorLocation();
	//We substract 400 from the Z value because of the location of the pivot of the SM
	Location.Z -= 400;
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AShockwave>(Location, Rotation, SpawnInfo);
}

void AMainChar::ChangeScale(bool Growth)
{
	FVector CurrentSize = GetMesh()->RelativeScale3D;
	FVector NewSize = CurrentSize;
	float ScaleChange = 0.01f;
	//Changing scale slowly to make it looking more pleasing
	if (Growth) {
		NewSize.X += ScaleChange;
		NewSize.Y += ScaleChange;
		NewSize.Z += ScaleChange;
		//X,Y,Z of NeedScaleChange are always equal
		NeededScaleChange.X -= ScaleChange;
		GetMesh()->SetRelativeScale3D(NewSize);
	}
	else {
		NewSize.X -= ScaleChange;
		NewSize.Y -= ScaleChange;
		NewSize.Z -= ScaleChange;
		//X,Y,Z of NeedScaleChange are always equal
		NeededScaleChange.X -= ScaleChange;
		GetMesh()->SetRelativeScale3D(NewSize);
	}
	//Growed to desired size?
	if (NeededScaleChange.X <= 0.f)bGrowthChange = false;
}

void AMainChar::CalculateScaleChange()
{
	float Percentage = CurrentWater / MaxWater;
	FVector CurrentScale = GetMesh()->RelativeScale3D;
	//If water depot is full characters mesh goes back to its normal size 
	if (Percentage == 1.f) {
		Growth = true;
		NeededScaleChange = NormalScale - CurrentScale;
	}else{
		//Calculates how much the character mesh needs to grow to achieve the calculated scale
		FVector NeededScale = NormalScale * Percentage;
		if (NeededScale.X < SmallestScale.X) NeededScale = SmallestScale;
		if (CurrentScale.X < NeededScale.X) {
			Growth = true;
			NeededScaleChange = NeededScale - CurrentScale;
		}
		else if (CurrentScale.X > NeededScale.X) {
			Growth = false;
			NeededScaleChange = CurrentScale - NeededScale;
		}
	}
	bGrowthChange = true;
}

void AMainChar::MakeVincible()
{
	Vincible = true;
}

void AMainChar::CleanDestroy()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Destroy();
}

void AMainChar::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (GP) {
		SpawnGroundPoundCollision();
		GP = false;
	}
	else HoverReleased();
}

void AMainChar::Blink()
{
	//Blinks and counts
	if (blinkcount < 6) {
		GetMesh()->SetVisibility(!(GetMesh()->IsVisible()));
		blinkcount++;
	}
	//If character blinked 6 times reset timer
	else {
		GetWorldTimerManager().ClearTimer(BlinkHandle);
		blinkcount = 0;
	}
}

void AMainChar::ChangeWaterLevel(float Val)
{
	//Checking if we can call simply RefillWaterCompletly to save resources
	if ((CurrentWater + Val) >= MaxWater)RefillWaterCompletely();
	else CurrentWater += Val;
	CalculateScaleChange();
}

void AMainChar::RefillWaterCompletely()
{
	CurrentWater = MaxWater;
	CalculateScaleChange();
}


float AMainChar::getCurrentWater()
{
	return CurrentWater;
}

float AMainChar::getMaxWater()
{
	return MaxWater;
}

void AMainChar::takeDamage()
{
	if (Vincible) {
		//Adding knnockback to the player
		FVector Knockback = FVector(GetActorForwardVector().X*(-5000000.f), GetActorForwardVector().Y*(-5000000.f),100000.f);
		GetCharacterMovement()->AddForce(Knockback);
		ChangeWaterLevel(-10.f);
		Vincible = false;
		//Timer for blinking at invicibility
		GetWorldTimerManager().SetTimer(VincibilityHandle, this,&AMainChar::MakeVincible, 1.5f , false);
		GetWorldTimerManager().SetTimer(BlinkHandle, this, &AMainChar::Blink, 0.25f,true,false);
	}
}

void AMainChar::upgradeMaxWater(float Val)
{
	MaxWater += Val;
}


