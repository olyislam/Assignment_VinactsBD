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



    to_Location = from_Location = GetOwner()->GetActorLocation();

    /*********************************************** Garbage will be remove this section ***************************************************/
    //float dst = -1;
    //APathNode* testGoalNode = nullptr;
    //for (TActorIterator<APathNode> availableNodes(GetWorld()); availableNodes; ++availableNodes)
    //{
    //    APathNode* node = *availableNodes;
    //    if (node)
    //    {
    //        float DistanceSquared = FVector::DistSquared(node->GetActorLocation(), GetOwner()->GetActorLocation());
    //        if (DistanceSquared > dst)
    //        {
    //            dst = DistanceSquared;
    //            testGoalNode = node;
    //        }
    //    }
    //}
    //SetDestination(testGoalNode);
    /*********************************************** Garbage will be remove this section ***************************************************/

}


// Called every frame
void UPathFollowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!shouldMove)
        return;
   
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



bool UPathFollowerComponent::SetRandomDestination(APathNode* ignoreableNode)
{
    if (ignoreableNode != nullptr)
        if (APathNode::nodes->Contains(ignoreableNode))
            APathNode::nodes->Remove(ignoreableNode);
        APathNode* closestNode = GetClosestPathNode();
        if(closestNode != nullptr)
            APathNode::nodes->Remove(closestNode);

        APathNode* goalNode = nullptr;
        if (APathNode::nodes->Num() > 0)
            goalNode = (*APathNode::nodes)[FMath::FRandRange(0, APathNode::nodes->Num() - 1)];
        
        if (ignoreableNode != nullptr)
            APathNode::nodes->Add(ignoreableNode);
        if (closestNode != nullptr)
            APathNode::nodes->Add(closestNode);

        if (goalNode != nullptr)
        {
            SetDestination(goalNode);
            return true;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Not Enough Path Node Available in the World Map to Generate A New Path!!!"));
            return false;
        }
    
        
}

bool UPathFollowerComponent::SetDestination(APathNode* destination)
{
    APathNode* startNode = GetClosestPathNode();
    if (startNode == nullptr || destination == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Input to Calculate Path!!!"));
 
        if (startNode == nullptr)
            UE_LOG(LogTemp, Warning, TEXT("Invalid Input to Calculate Path!!! 1"));
        if (destination == nullptr)
            UE_LOG(LogTemp, Warning, TEXT("Invalid Input to Calculate Path!!! 2"));

        return false;
    }
    

	path = VinactsBDAssignmentPathFinder::FindPath(startNode, destination);
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

APathNode* UPathFollowerComponent::GetClosestPathNode()
{
    APathNode* result = nullptr;
    float distSqrt = MAX_FLT;
    const FVector relativePoint = GetOwner()->GetActorLocation();

    for (APathNode* node : *APathNode::nodes)
    {
        if (node)
        {
            float dist = FVector::DistSquared(node->GetActorLocation(), relativePoint);
            if (dist < distSqrt)
            {
                distSqrt = dist;
                result = node;
            }
        }
    }

    if (result == nullptr)
        UE_LOG(LogTemp, Warning, TEXT("No any Closest path Node Found"));

    return result;
}