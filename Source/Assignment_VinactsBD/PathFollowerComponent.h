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
	bool SetDestination(APathNode* destination);
private:
	APathNode* GetClosestNode(AActor& from);
	void UpdatePathLineSegment();


protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VinactsBD Assignment")
		float speed = 1;
	APathNode* lastReachedNode;

private:
	float t = 0;
	float dt = 0;
	float selectedIndex = 1;
	FVector from_Location;
	FVector to_Location;
	TArray<APathNode*> path;
};
