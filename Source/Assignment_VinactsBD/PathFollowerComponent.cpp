// Fill out your copyright notice in the Description page of Project Settings.

#include "Assignment_VinactsBDGameMode.h"
#include "VinactsBDAssignmentPathFinder.h"
#include "EngineUtils.h"
#include "Containers/Array.h"
#include "PathNode.h"
#include "PathFollowerComponent.h"
#include "Algo/Transform.h"


// Sets default values for this component's properties
UPathFollowerComponent::UPathFollowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPathFollowerComponent::BeginPlay()
{
	Super::BeginPlay();	
    lastReachedNode = UPathFollowerComponent::GetClosestNode(*GetOwner());
}


// Called every frame
void UPathFollowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


    if (lastReachedNode == nullptr)
        return;
    FVector direction = lastReachedNode->GetActorLocation() - GetOwner()->GetActorLocation();
    direction/= direction.Length();
	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + direction);
	// ...
}


void UPathFollowerComponent::SetDestination(APathNode* destination)
{
    if(lastReachedNode == nullptr)
        lastReachedNode = UPathFollowerComponent::GetClosestNode(*GetOwner()); 

    if (lastReachedNode == nullptr)
        return;
    
	path = VinactsBDAssignmentPathFinder::FindPath(lastReachedNode, destination);
}

APathNode* UPathFollowerComponent::GetClosestNode(AActor& from)
{
    APathNode* result = nullptr;
    float ClosestDistanceSquared = MAX_FLT;
    for (TActorIterator<APathNode> availableNodes(GetWorld()); availableNodes; ++availableNodes)
    {
        APathNode* node = *availableNodes;
        if (node)
        {
            float DistanceSquared = FVector::DistSquared(node->GetActorLocation(), GetOwner()->GetActorLocation());
            if (DistanceSquared < ClosestDistanceSquared)
            {
                ClosestDistanceSquared = DistanceSquared;
                result = node;
            }
        }
    }

    if (result == nullptr)
        UE_LOG(LogTemp, Warning, TEXT("No any relative path node found to create a complete path.\nPlease construct the path node properly in the map"));

    return result;
}