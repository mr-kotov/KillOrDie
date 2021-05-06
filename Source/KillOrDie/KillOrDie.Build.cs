// Kill or Die

using UnrealBuildTool;

public class KillOrDie : ModuleRules
{
	public KillOrDie(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "InputCore"});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[]
		{
			"KillOrDie/Public/Characters",
			"KillOrDie/Public/Characters/Components",
			"KillOrDie/Public/GameModes",
			"KillOrDie/Public/Dev",
			"KillOrDie/Public/Weapons",
			"KillOrDie/Public/Weapons/Launcher",
			"KillOrDie/Public/Weapons/Rifle",
			"KillOrDie/Public/UI",
			"KillOrDie/Public/Characters/Animations",
			"KillOrDie/Public/UI"
		});

		// Uncomment if you are using Slate UI
		//PrivateDependencyModuleNames.AddRange();

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}