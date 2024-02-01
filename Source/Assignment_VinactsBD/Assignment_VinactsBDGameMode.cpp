// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment_VinactsBDGameMode.h"
#include "Assignment_VinactsBDCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAssignment_VinactsBDGameMode::AAssignment_VinactsBDGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Assignment_Files/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
