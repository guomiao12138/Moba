// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Protobuf : ModuleRules
{
	public Protobuf(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
/*		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;*/

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
			PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "libprotobuf.lib"));
		}

		ShadowVariableWarningLevel = WarningLevel.Off;
        bEnableUndefinedIdentifierWarnings = false;
		bEnableExceptions = true;
		PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");
		
		PublicIncludePaths.Add(ModuleDirectory);
	}
}
