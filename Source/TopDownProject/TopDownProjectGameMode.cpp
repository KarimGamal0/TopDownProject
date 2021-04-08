// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownProjectGameMode.h"
#include "TopDownProjectPlayerController.h"
#include "TopDownProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopDownProjectGameMode::ATopDownProjectGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopDownProjectPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}