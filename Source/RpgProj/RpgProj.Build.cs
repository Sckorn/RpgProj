// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RpgProj : ModuleRules
{
	public RpgProj(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Json", "JsonUtilities" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore"});
	}
}
