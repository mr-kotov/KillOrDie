// Kill or Die

using UnrealBuildTool;
using System.Collections.Generic;

public class KillOrDieTarget : TargetRules
{
	public KillOrDieTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "KillOrDie" } );
	}
}
