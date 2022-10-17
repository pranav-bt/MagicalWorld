// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MagicalWorld : ModuleRules
{
	public MagicalWorld(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" , "GameplayTags", "UMG", "Slate", "SlateCore"});

	}
}
