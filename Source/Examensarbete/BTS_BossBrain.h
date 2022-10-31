// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_BossBrain.generated.h"

/**
 * 
 */
UCLASS()
class EXAMENSARBETE_API UBTS_BossBrain : public UBTService
{
	GENERATED_BODY()

public:
	UBTS_BossBrain();

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Player;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector EnemyState;
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;



private:

};
