// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class Protobuf : ModuleRules
{
	public Protobuf(ReadOnlyTargetRules Target) : base(Target)
	{
        Type = ModuleType.External;

        ShadowVariableWarningLevel = WarningLevel.Off;
        bEnableUndefinedIdentifierWarnings = false;
        bEnableExceptions = true;
        PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");
        PublicDefinitions.Add("PROTOBUF_VERSION");

        string LibraryPath = Path.Combine(ModuleDirectory, "lib");

        PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
/*        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));*/

        if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "Win64", "libprotobuf.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "Win64", "libprotoc.lib"));
        }


	}
}
