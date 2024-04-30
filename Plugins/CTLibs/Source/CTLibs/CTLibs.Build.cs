// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class CTLibs : ModuleRules
{
	public CTLibs(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);

        // Get the engine path. Ends with "Engine/"
        string engine_path = Path.GetFullPath(Target.RelativeEnginePath);
        string srcrt_path = engine_path + "Source/Runtime/Renderer/Private";

        PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
				srcrt_path
            }
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				"Projects",
                "RenderCore",
                "Renderer",
                "RHI"
				// ... add private dependencies that you statically link with here ...	
			}
			);

        DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
