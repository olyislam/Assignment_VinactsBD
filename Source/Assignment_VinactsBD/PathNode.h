#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"
#include "PathNode.generated.h"

UCLASS()
class ASSIGNMENT_VINACTSBD_API APathNode : public AActor
{
	GENERATED_BODY()

public:
	// Declare a static TArray variable
	static TArray<APathNode*>* nodes;

	// Sets default values for this actor's properties
	APathNode();

	UPROPERTY(EditAnywhere, Category = "VinactsBD Assignment")
		TArray<APathNode*> neighbors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
