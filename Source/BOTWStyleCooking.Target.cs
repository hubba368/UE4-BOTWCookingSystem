// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class BOTWStyleCookingTarget : TargetRules
{
	public BOTWStyleCookingTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "BOTWStyleCooking" } );
	}
}
