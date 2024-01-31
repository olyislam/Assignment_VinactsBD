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
//    lastReachedNode = UPathFollowerComponent::GetClosestNode(*GetOwner());





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
    if (!shouldMove)
        return;

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
    {
        if (lastReachedNode != nullptr)
        {
            lastReachedNode = path.Last();
            onOnReachedEndNode.Broadcast(lastReachedNode);
            UE_LOG(LogTemp, Warning, TEXT("You Reached The End Node At Location: %s"), *lastReachedNode->GetActorLocation().ToString());
            lastReachedNode = nullptr;
        }
        return;
    }

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
    UE_LOG(LogTemp, Warning, TEXT("New Path Node Index: %d"), selectedIndex);
    
    t = 0;
    dt = (1.0 / FVector::Distance(from_Location, to_Location)) * speed;

    if (lastReachedNode != nullptr)
    {
        onReachedPathNode.Broadcast(lastReachedNode);
        UE_LOG(LogTemp, Warning, TEXT("You Reached the Node: %s At Location: %s"), *lastReachedNode->GetName(), *lastReachedNode->GetActorLocation().ToString());
    }
}


bool UPathFollowerComponent::SetDestination(APathNode* destination)
{
    APathNode* closestNode = GetClosestNode(*GetOwner());
    if (closestNode == nullptr || destination == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Input to Calculate Path!!!"));
        return false;
    }
    

	path = VinactsBDAssignmentPathFinder::FindPath(closestNode, destination);
    if (path.Num() < 1)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Path!!!"));
        return false;
    }

    float offsetFromFirstNode = FVector::Distance(GetOwner()->GetActorLocation(), path.Top()->GetActorLocation());
    UE_LOG(LogTemp, Warning, TEXT("\n\nPath Node Count: %d\nOffset Between Object To Path Start Node %d\n"), path.Num(), offsetFromFirstNode);

    selectedIndex = offsetFromFirstNode > 0 ? -1 : 0;
    UpdatePathLineSegment();
    return true;
}

APathNode* UPathFollowerComponent::GetClosestNode(AActor& from)
{
    APathNode* result = nullptr;
    float ClosestDistanceSquared = MAX_FLT;
    APathNode* node = nullptr;
    for (TActorIterator<APathNode> availableNodes(GetWorld()); availableNodes; ++availableNodes)
    {
         node = *availableNodes;
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