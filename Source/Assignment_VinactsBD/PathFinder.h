// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathNode.h"
#include "Containers/Array.h"
#include "PathFinder.generated.h"

UCLASS()
class ASSIGNMENT_VINACTSBD_API APathFinder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathFinder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	UPROPERTY(EditAnywhere, Category = "VinactsBD Assignment")
		APathNode* startNode;
	UPROPERTY(EditAnywhere, Category = "VinactsBD Assignment")
		APathNode* goalNode;

	static TArray<APathNode*> FindPath(const APathNode* startNode, const APathNode* goalNode);
	static TArray<APathNode*> ReconstructPath(const TMap<APathNode*, APathNode*>& cameFrom, const APathNode* current);
	 
	static APathNode* GetNodeWithLowestFScore(const TArray<APathNode*>& openSet, const TMap<APathNode*, float>& fScore);
 	static float HeuristicCostEstimate(const APathNode& from, const APathNode& to);
	static float CostToMove(const APathNode& from, const APathNode& to);

	void TestDelay();

};
