// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM415_FPSGameMode.h"
#include "GAM415_FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGAM415_FPSGameMode::AGAM415_FPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
