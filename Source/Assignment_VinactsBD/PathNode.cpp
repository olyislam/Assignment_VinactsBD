#include "PathNode.h"
#include "Containers/Array.h"

// Define the static variable here
TArray<APathNode*>* APathNode::nodes = nullptr;

// Sets default values
APathNode::APathNode()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APathNode::BeginPlay()
{
	Super::BeginPlay();

	if (nodes == nullptr)
		nodes = new TArray<APathNode*>();
	
	if (!nodes->Contains(this))
	{
		nodes->Add(this);
		UE_LOG(LogTemp, Warning, TEXT("Total Path Node Count: %d"), nodes->Num());
	}
}
