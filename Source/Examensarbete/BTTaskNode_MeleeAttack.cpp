// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_MeleeAttack.h"

#include "AIController.h"
#include "FPSCharacter.h"

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

	AFPSCharacter* Character =  Cast<AFPSCharacter>(OwnerComp.GetAIOwner()->GetPawn()) ;

	if (Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Character -> Shoot();
	
	return EBTNodeResult::Succeeded;
}
