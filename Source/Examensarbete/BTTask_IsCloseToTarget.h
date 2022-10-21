// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_IsCloseToTarget.generated.h"

/**
 * 
 */
UCLASS()
class EXAMENSARBETE_API UBTTask_IsCloseToTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_IsCloseToTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere)
	float AttackRange;
};
