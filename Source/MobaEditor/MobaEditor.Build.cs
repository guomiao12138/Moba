// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class MobaEditor : ModuleRules
{
	public MobaEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "AnimGraphRuntime",
        });

		PrivateDependencyModuleNames.AddRange(new string[] {
        });
    }
}
