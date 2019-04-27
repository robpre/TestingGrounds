// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
// TODO unlink this architecture
#include "PatrollingGuard.h"
#include "Classes/AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
    auto Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);

    AAIController* AIOwner = OwnerComp.GetAIOwner();

    if (!AIOwner || !AIOwner->GetPawn()) { return EBTNodeResult::Failed; }

    TArray<AActor*> PatrolPoints = GetPatrolPoints(AIOwner->GetPawn());

    if (PatrolPoints.Num() == 0) { return EBTNodeResult::Failed; }

    BlackboardComponent->SetValueAsObject(
        NextWaypointKey.SelectedKeyName,
        PatrolPoints[Index]
    );

    auto NextIndex = ++Index % PatrolPoints.Num();

    BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

    // UE_LOG(LogTemp, Warning, TEXT("Boop my snoot %i"), Index);

    return EBTNodeResult::Succeeded;
}

TArray<AActor*> UChooseNextWaypoint::GetPatrolPoints(APawn* ControlledPawn) const {
    APatrollingGuard* Guard = Cast<APatrollingGuard>(ControlledPawn);

    return Guard->PatrolPoints;
}
