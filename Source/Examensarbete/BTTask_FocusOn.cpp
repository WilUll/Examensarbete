// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FocusOn.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Kismet/KismetMathLibrary.h"

UBTTask_FocusOn::UBTTask_FocusOn()
{
	NodeName = "Focus On";
}

EBTNodeResult::Type UBTTask_FocusOn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	AActor* SelfActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor")));

	FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(SelfActor->GetActorLocation(), Target->GetActorLocation());

	SelfActor->SetActorRotation(PlayerRot);
	return EBTNodeResult::Succeeded;
}
