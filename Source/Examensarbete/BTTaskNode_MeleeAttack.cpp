// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_MeleeAttack.h"

#include "AICharacter.h"
#include "AIController.h"

UBTTaskNode_MeleeAttack::UBTTaskNode_MeleeAttack()
{
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTaskNode_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AAICharacter* AICharacter =  Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (AICharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AICharacter -> Attack();
	
	return EBTNodeResult::Succeeded;
}
