// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "UnrealPlayground.h"
#include "UnrealPlaygroundGameMode.h"
#include "UnrealPlaygroundHUD.h"
#include "UnrealPlaygroundCharacter.h"

AUnrealPlaygroundGameMode::AUnrealPlaygroundGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUnrealPlaygroundHUD::StaticClass();
}
