// Fill out your copyright notice in the Description page of Project Settings.
#include "PathFollowerComponent.h"
#include "PathFollowerComponent.h"
#include "Assignment_VinactsBDGameMode.h"
#include "VinactsBDAssignmentPathFinder.h"
#include "EngineUtils.h"
#include "Containers/Array.h"
#include "PathNode.h"
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





    /*********************************************** Garbage will be remove this section ***************************************************/
    float dst = -1;
    APathNode* testGoalNode = nullptr;
    for (TActorIterator<APathNode> availableNodes(GetWorld()); availableNodes; ++availableNodes)
    {
        APathNode* node = *availableNodes;
        if (node)
        {
            float DistanceSquared = FVector::DistSquared(node->GetActorLocation(), GetOwner()->GetActorLocation());
            if (DistanceSquared > dst)
            {
                dst = DistanceSquared;
                testGoalNode = node;
            }
        }
    }
    SetDestination(testGoalNode);
    /*********************************************** Garbage will be remove this section ***************************************************/

}


// Called every frame
void UPathFollowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
   
    t = FMath::Clamp(t + dt, 0, 1);
    FVector newPoint = FMath::Lerp(from_Location, to_Location, t);
	GetOwner()->SetActorLocation(newPoint);

    if (t == 1)
        UpdatePathLineSegment();
}


void UPathFollowerComponent::UpdatePathLineSegment()
{
    if (selectedIndex >= path.Num() - 1)
        return;

    if (selectedIndex >= 0)
    {
        lastReachedNode = path[selectedIndex];
        from_Location = lastReachedNode->GetActorLocation();
    }
    else
    {
        lastReachedNode = nullptr;
        from_Location = GetOwner()->GetActorLocation();
    }

    to_Location = path[++selectedIndex]->GetActorLocation();
    UE_LOG(LogTemp, Warning, TEXT("Selected Index IS %d"), selectedIndex);
    
    t = 0;
    dt = (1.0 / FVector::Distance(from_Location, to_Location)) * speed;

    if(lastReachedNode != nullptr)
        UE_LOG(LogTemp, Warning, TEXT("You Reached the Node: %s At Location: %s"), *lastReachedNode->GetName(), *lastReachedNode->GetActorLocation().ToString());
}



bool UPathFollowerComponent::SetDestination(APathNode* destination)
{
    if(lastReachedNode == nullptr)
        lastReachedNode = GetClosestNode(*GetOwner()); 
    if (lastReachedNode == nullptr || destination == nullptr)
        return false;
    

	path = VinactsBDAssignmentPathFinder::FindPath(lastReachedNode, destination);

    selectedIndex = -1;
    UpdatePathLineSegment();

    UE_LOG(LogTemp, Warning, TEXT("Path Follower component path node count %d"), path.Num());

    return true;
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