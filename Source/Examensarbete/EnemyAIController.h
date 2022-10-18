// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class EXAMENSARBETE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
