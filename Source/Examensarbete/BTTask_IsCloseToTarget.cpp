// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IsCloseToTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_IsCloseToTarget::UBTTask_IsCloseToTarget()
{
	NodeName = TEXT("Is Close To Target");
}

EBTNodeResult::Type UBTTask_IsCloseToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (Target == nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsCloseToTarget"), false);
		return EBTNodeResult::Failed;
	}

	if (FVector::Dist(Target->GetActorLocation(), UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation()) < AttackRange)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsCloseToTarget"), true);
		return EBTNodeResult::Succeeded;
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsCloseToTarget"), false);
	return EBTNodeResult::Failed;
}
