// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/Pawn.h"
#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PathNode.h"
#include "Assignment_VinactsBDCharacter.generated.h"

UCLASS(config=Game)
class AAssignment_VinactsBDCharacter : public APawn
{
	GENERATED_BODY()
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VinactsBD Assignment", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VinactsBD Assignment", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

public:
	AAssignment_VinactsBDCharacter();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

private:
	virtual void InputBegin();
	virtual void InputReleased();
	virtual void InpuTriggered();
};

