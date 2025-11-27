// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NetSimProject : ModuleRules
{
	public NetSimProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
            "Networking",
            "Sockets",
            "NavigationSystem"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"NetSimProject",
			"NetSimProject/Variant_Platforming",
			"NetSimProject/Variant_Platforming/Animation",
			"NetSimProject/Variant_Combat",
			"NetSimProject/Variant_Combat/AI",
			"NetSimProject/Variant_Combat/Animation",
			"NetSimProject/Variant_Combat/Gameplay",
			"NetSimProject/Variant_Combat/Interfaces",
			"NetSimProject/Variant_Combat/UI",
			"NetSimProject/Variant_SideScrolling",
			"NetSimProject/Variant_SideScrolling/AI",
			"NetSimProject/Variant_SideScrolling/Gameplay",
			"NetSimProject/Variant_SideScrolling/Interfaces",
			"NetSimProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
