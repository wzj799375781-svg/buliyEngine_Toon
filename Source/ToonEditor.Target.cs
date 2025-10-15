// buliy

using UnrealBuildTool;
using System.Collections.Generic;

public class ToonEditorTarget : TargetRules
{
	public ToonEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "Toon" } );
	}
}
