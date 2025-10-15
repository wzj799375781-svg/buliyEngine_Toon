// buliy

using UnrealBuildTool;
using System.Collections.Generic;

public class ToonTarget : TargetRules
{
	public ToonTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "Toon" } );
	}
}
