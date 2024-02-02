// Fill out your copyright notice in the Description page of Project Settings.


#include "PathRendererComponent.h"

// Sets default values for this component's properties
UPathRendererComponent::UPathRendererComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called every frame
void UPathRendererComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (int i = 1; i < path.Num(); i++)
		DrawDebugLine(GetWorld(), path[i - 1]->GetActorLocation() + offsetFromPoint, path[i]->GetActorLocation() + offsetFromPoint, FColor::Green);
}

void UPathRendererComponent::SetPath(TArray<APathNode*> newPath)
{
	path = newPath;
}

