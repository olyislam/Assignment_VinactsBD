#include "Assignment_VinactsBDCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "PathNode.h"
#include "EnhancedInputSubsystems.h"

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

void AAssignment_VinactsBDCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//Binding input to show the debug on console
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AAssignment_VinactsBDCharacter::InputBegin);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AAssignment_VinactsBDCharacter::InputReleased);
	}
}

void AAssignment_VinactsBDCharacter::InputBegin()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Input Begin"));
}

void AAssignment_VinactsBDCharacter::InputReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Input Released"));
}



