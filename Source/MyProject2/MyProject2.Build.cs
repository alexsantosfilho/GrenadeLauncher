// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProject2 : ModuleRules
{
	public MyProject2(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "RHI", "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "GameplayTasks", "UMG", "Slate", "SlateCore" });
        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
