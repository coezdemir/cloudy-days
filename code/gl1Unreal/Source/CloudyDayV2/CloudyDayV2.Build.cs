// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CloudyDayV2 : ModuleRules
{
	public CloudyDayV2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","UMG","MoviePlayer"});
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
