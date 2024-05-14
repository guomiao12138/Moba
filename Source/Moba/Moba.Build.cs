// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Moba : ModuleRules
{
	public Moba(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = true;

        PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject",
			"Engine", 
			"InputCore",
            "AIModule",
            "Ability",
            "Sockets",
            "Networking",
            "MobaProtobufLibrary",
        });

<<<<<<< HEAD
		PrivateDependencyModuleNames.AddRange(new string[] {  });
=======
		PrivateDependencyModuleNames.AddRange(new string[] {
/*            "DeveloperSettings"*/
        });
>>>>>>> 8c2da2788208675a659dddd96673535840c0f068

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "../../Config", "DefaultMobaInputSetting.ini"));
/*        RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "../../Plugins", "Ability"));*/
    }
}
