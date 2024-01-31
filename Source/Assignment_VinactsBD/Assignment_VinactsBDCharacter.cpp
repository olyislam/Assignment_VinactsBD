// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment_VinactsBDCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "PathNode.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// AAssignment_VinactsBDCharacter

AAssignment_VinactsBDCharacter::AAssignment_VinactsBDCharacter()
{
}

void AAssignment_VinactsBDCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAssignment_VinactsBDCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AAssignment_VinactsBDCharacter::InputBegin);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAssignment_VinactsBDCharacter::InpuTriggered);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AAssignment_VinactsBDCharacter::InputReleased);
	}
}

void AAssignment_VinactsBDCharacter::InputBegin()
{
	// Add a log statement to confirm Intensity changes
	UE_LOG(LogTemp, Warning, TEXT("InputBegin"));

}

void AAssignment_VinactsBDCharacter::InputReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("InputReleased"));
}


void AAssignment_VinactsBDCharacter::InpuTriggered()
{
	UE_LOG(LogTemp, Warning, TEXT("InpuTriggered"));
}



