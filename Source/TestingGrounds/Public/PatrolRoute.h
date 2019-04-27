// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPatrolRoute();

protected:
	UPROPERTY(EditInstanceOnly, Category = "Patrolling")
	TArray<AActor*> PatrolPoints;

public:
	TArray<AActor*> GetPatrolPoints() const;
};
