// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VoicePeakUE5 : ModuleRules
{
	public VoicePeakUE5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "Engine",
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
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
		if (Target.bBuildEditor == true)
		{
			// @todo api: Only public because of WITH_EDITOR and UNREALED_API
			PublicDependencyModuleNames.Add("EditorFramework");
			PublicDependencyModuleNames.Add("UnrealEd");
			CircularlyReferencedDependentModules.Add("UnrealEd");
		}
	}
}
