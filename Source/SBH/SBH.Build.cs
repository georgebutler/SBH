// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SBH : ModuleRules
{
	public SBH(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"ModularGameplay",
			"ModularGameplayActors",
			"EnhancedInput",
			"UMG",
			
			"EasyMultiSave",
			"DialoguePlugin"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
