// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PathNode.h"
#include "Containers/Array.h"
#include "PathFollowerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASSIGNMENT_VINACTSBD_API UPathFollowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPathFollowerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "VinactsBD Assignment")
	void SetDestination(APathNode* destination);
private:
	APathNode* GetClosestNode(AActor& from);

protected:
	APathNode* lastReachedNode;

private:
	TArray<APathNode*> path;
};
