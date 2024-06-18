// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class MobaEditor : ModuleRules
{
	public MobaEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        OverridePackageType = PackageOverrideType.GameUncookedOnly;
        PublicDependencyModuleNames.AddRange(new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "BlueprintGraph",
                "Moba",
                "AnimGraph"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {
        });
    }
}
