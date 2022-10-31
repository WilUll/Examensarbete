// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_Attack.h"

#include "Engine.h"

void UAN_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);
}
