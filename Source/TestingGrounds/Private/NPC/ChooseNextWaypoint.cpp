// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h"
#include "NPC/PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
    auto Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);

    AAIController* AIOwner = OwnerComp.GetAIOwner();

    if (!ensure(AIOwner)) { return EBTNodeResult::Failed; }

    TArray<AActor*> PatrolPoints = GetPatrolPoints(AIOwner->GetPawn());

    if (PatrolPoints.Num() == 0) {
        UE_LOG(LogTemp, Warning, TEXT("AI:%s is missing PatrolPoints"), *AIOwner->GetName());

        return EBTNodeResult::Failed;
    }

    BlackboardComponent->SetValueAsObject(
        NextWaypointKey.SelectedKeyName,
        PatrolPoints[Index]
    );

    auto NextIndex = ++Index % PatrolPoints.Num();

    BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

    return EBTNodeResult::Succeeded;
}

TArray<AActor*> UChooseNextWaypoint::GetPatrolPoints(APawn* ControlledPawn) const {
    if (!ensure(ControlledPawn)) { return TArray<AActor*>(); }

    UPatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

    if (!ensure(PatrolRoute)) { return TArray<AActor*>(); }

    return PatrolRoute->GetPatrolPoints();
}
