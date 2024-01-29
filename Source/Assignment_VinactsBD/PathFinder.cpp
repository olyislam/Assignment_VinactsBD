// Fill out your copyright notice in the Description page of Project Settings.

#include "Containers/Array.h"
#include "PathFinder.h"

// Sets default values
APathFinder::APathFinder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APathFinder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APathFinder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



TArray<APathNode*> APathFinder::FindPath(const APathNode* startNode, const APathNode* goalNode)
{
	TArray<APathNode*>* openSet = new TArray<APathNode*>();
	TArray<APathNode*>* closedSet = new TArray<APathNode*>();

	TMap<APathNode*, APathNode*>* cameFrom = new TMap<APathNode*, APathNode*>();
	TMap<APathNode*, float>* gScore = new TMap<APathNode*, float>();
	TMap<APathNode*, float>* fScore = new TMap<APathNode*, float>();

	APathNode* current = const_cast<APathNode*>(startNode);
	openSet->Add(current);
	gScore->Add(current, 0.0f);
	fScore->Add(current, HeuristicCostEstimate(*startNode, *goalNode));

	while (openSet->Num() > 0)
	{
		current = GetNodeWithLowestFScore(*openSet, *fScore);
		if (current == goalNode)
			return ReconstructPath(*cameFrom, current);

		openSet->Remove(current);
		closedSet->Add(current);


		for (APathNode* neighbor : current->neighbors)
		{
			if (closedSet->Contains(neighbor))
				continue;

			float tentativeGScore = *gScore->Find(current) + APathFinder::CostToMove(*current, *neighbor);

			if (!openSet->Contains(neighbor) || tentativeGScore < *gScore->Find(neighbor))
			{
				cameFrom->Add(neighbor, current);
				gScore->Add(neighbor, tentativeGScore);
				fScore->Add(neighbor, *gScore->Find(neighbor) + APathFinder::HeuristicCostEstimate(*neighbor, *goalNode));

				if (!openSet->Contains(neighbor))
					openSet->Add(neighbor);
			}
		}
	}

	return TArray<APathNode*>();
}

TArray<APathNode*> APathFinder::ReconstructPath(const TMap<APathNode*, APathNode*>& cameFrom, const APathNode* current)
{
	TArray<APathNode*> path = TArray<APathNode*>();
	while (cameFrom.Contains(current))
	{
		path.Insert(const_cast<APathNode*>(current), 0);
		current = cameFrom.FindRef(current);
	}
	path.Insert(const_cast<APathNode*>(current), 0);
	return path;
}

APathNode* APathFinder::GetNodeWithLowestFScore(const TArray<APathNode*>& openSet, const TMap<APathNode*, float>& fScore)
{
	if (openSet.Num() == 0)
		return nullptr;

	APathNode* lowestNode = openSet.Top();
	for (APathNode* node : openSet)
		if (fScore.Find(node) < fScore.Find(lowestNode))
			lowestNode = node;

	return lowestNode;
}


float APathFinder::HeuristicCostEstimate(const APathNode& from, const APathNode& to)
{
	return FVector::Distance(from.GetActorLocation(), to.GetActorLocation());
}

float APathFinder::CostToMove(const APathNode& from, const APathNode& to)
{
	return APathFinder::HeuristicCostEstimate(from, to);
}

