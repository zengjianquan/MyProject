// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProject : ModuleRules
{
	public MyProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "CTLibs"});

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"GameplayAbilities", 
			"GameplayTags", 
			"GameplayTasks",
            "NavigationSystem",
			"Niagara",

            "OnlineSubsystem",
            "OnlineSubsystemNull"
        });
        

    }
}
