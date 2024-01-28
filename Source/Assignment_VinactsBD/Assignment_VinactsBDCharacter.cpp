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
	t = new float(0.0);
	dt = new float(0.0);
	from = new FVector();
	to = new FVector();
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
	to->X = 10;
	*dt = 1.0 / (FVector::Distance(*from, *to) * 60.0);

	UE_LOG(LogTemp, Warning, TEXT("MyDoubleValue: %s"), *FString::Printf(TEXT("%f"), *dt));
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


void AAssignment_VinactsBDCharacter::SetEdgeToFollow(const APathNode* a, const APathNode* b)
{
	if (a == nullptr || b == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("You passed null Path Node pointer"));
		return;
	}

	*from = a->GetActorLocation();
	*to = b->GetActorLocation();
	
	*t += *dt;
	UE_LOG(LogTemp, Warning, TEXT("Set Node Edge\nT: %f DT: %f From: %s To: %s"), *t, *dt, *(*from).ToString(), *(*to).ToString());
}
void AAssignment_VinactsBDCharacter::InpuTriggered()
{
	FVector LerpedVector = FMath::Lerp(*from, *to, *t);
	*t += *dt;
	// Print the result to the log
	UE_LOG(LogTemp, Warning, TEXT("T: %f DT: %f From: %s To: %s"), *t, *dt, *(*from).ToString(), *(*to).ToString());

	//UE_LOG(LogTemp, Warning, TEXT("InpuTriggered"));
}



