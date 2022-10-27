// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveAwayFrom.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MoveAwayFrom::UBTTask_MoveAwayFrom()
{
	NodeName = TEXT("Move Away From");
}

EBTNodeResult::Type UBTTask_MoveAwayFrom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	AActor* SelfActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor")));
	
	FVector Location = SelfActor->GetActorLocation() + ((SelfActor->GetActorForwardVector()	 + Target->GetActorForwardVector()) * Range);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("Location"), Location);

	return EBTNodeResult::Succeeded;
}
