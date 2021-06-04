// Kill or Die

using UnrealBuildTool;

public class KillOrDie : ModuleRules
{
	public KillOrDie(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"Niagara", 
			"PhysicsCore",
			"GameplayTasks",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[]
		{
			"KillOrDie/Public/Characters",
			"KillOrDie/Public/Characters/Components",
			"KillOrDie/Public/GameModes",
			"KillOrDie/Public/Player",
			"KillOrDie/Public/Dev",
			"KillOrDie/Public/Weapons",
			"KillOrDie/Public/Weapons/Launcher",
			"KillOrDie/Public/Weapons/Rifle",
			"KillOrDie/Public/Weapons/Components",
			"KillOrDie/Public/UI",
			"KillOrDie/Public/Characters/Animations",
			"KillOrDie/Public/UI",
			"KillOrDie/Public/Pickups",
			"KillOrDie/Public/AI",
			"KillOrDie/Public/AI/Tasks",
			"KillOrDie/Public/AI/Components",
			"KillOrDie/Public/AI/Services",
			"KillOrDie/Public/AI/EQS",
			"KillOrDie/Public/AI/Decorators"
		});

		// Uncomment if you are using Slate UI
		//PrivateDependencyModuleNames.AddRange();

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}