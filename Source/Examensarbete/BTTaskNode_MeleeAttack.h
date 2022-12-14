// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class EXAMENSARBETE_API UBTTaskNode_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_MeleeAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
