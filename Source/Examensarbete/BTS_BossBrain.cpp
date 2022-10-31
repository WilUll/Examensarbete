// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_BossBrain.h"

#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BTFunctionLibrary.h"

UBTS_BossBrain::UBTS_BossBrain()
{
	NodeName = "Boss Brain";

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UBTS_BossBrain::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTS_BossBrain::InitializeFromAsset(UBehaviorTree& Asset)
{
	
}

void UBTS_BossBrain::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	
}
