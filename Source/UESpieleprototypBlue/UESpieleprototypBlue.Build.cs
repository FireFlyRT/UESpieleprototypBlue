// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class UESpieleprototypBlue : ModuleRules
{
	public UESpieleprototypBlue(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "RenderCore", "RHI", "EnhancedInput", "GeometryScriptingCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivateIncludePaths.Add("P:/Program Files/Epic Games/UE_5.2/Engine/Binaries/ThirdParty/Python3/Win64/libs");

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
