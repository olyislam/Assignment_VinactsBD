// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PathNode.h"
#include "Assignment_VinactsBDCharacter.generated.h"

UCLASS(config=Game)
class AAssignment_VinactsBDCharacter : public ACharacter
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

	UFUNCTION(BlueprintCallable, Category = "VinactsBD Assignment")
		virtual void SetEdgeToFollow(const APathNode* a, const APathNode* b);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

private:
	float* t;
	float* dt;
	FVector* from;
	FVector* to;

	virtual void InputBegin();
	virtual void InputReleased();
	virtual void InpuTriggered();

};

