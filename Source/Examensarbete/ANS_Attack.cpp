// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_Attack.h"

#include "AICharacter.h"

class AAICharacter;

void UANS_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Green, __FUNCTION__);
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		AAICharacter* AI = Cast<AAICharacter>(MeshComp->GetOwner());
		if (AI != nullptr)
		{
			AI->AttackStart();
		}
	}
}

void UANS_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Red, __FUNCTION__);
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		AAICharacter* AI = Cast<AAICharacter>(MeshComp->GetOwner());
		if (AI != nullptr)
		{
			AI->AttackEnd();
		}
	}
}
