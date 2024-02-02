// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PathNode.h"
#include "Containers/Array.h"
#include "PathFollowerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPathNodeEvent, class APathNode*, PathNode);

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
	UFUNCTION(BlueprintCallable, Category = "VinactsBD Assignment")
		bool SetRandomDestination(APathNode* ignoreableNode);
	
	UPROPERTY(BlueprintAssignable, Category = "VinactsBD Assignment")
		FPathNodeEvent onReachedPathNode;
	UPROPERTY(BlueprintAssignable, Category = "VinactsBD Assignment")
		FPathNodeEvent onOnReachedEndNode;

private:
	APathNode* GetClosestPathNode();
	void UpdatePathLineSegment();


protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VinactsBD Assignment")
		float speed = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VinactsBD Assignment")
		bool shouldMove = false;


private:
	float t = 0;
	float dt = 0;
	int selectedIndex = 1;
	FVector from_Location;
	FVector to_Location;

	TArray<APathNode*> path;
	APathNode* lastReachedNode;
};
