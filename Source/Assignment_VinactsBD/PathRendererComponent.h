// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PathNode.h"
#include "Components/ActorComponent.h"
#include "PathRendererComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASSIGNMENT_VINACTSBD_API UPathRendererComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPathRendererComponent();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "VinactsBD Assignment")
		void SetPath(TArray<APathNode*> newPath);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VinactsBD Assignment")
		FVector offsetFromPoint = FVector(0, 0, 10);


private:
	TArray<APathNode*> path;
		
};
