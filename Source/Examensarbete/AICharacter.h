// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class EXAMENSARBETE_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ToggleWeaponColliders(bool TrueOrFalse) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category = "Health")
	class UHealthComponent* HealthComponent;

	APawn* PlayerPawn;

	UPROPERTY(EditDefaultsOnly)
	float DamageAmount;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = "Combat")
	UBoxComponent* LAttackCollider;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = "Combat")
	UBoxComponent* RAttackCollider;

	void AttackStart();

	void AttackEnd();

	UFUNCTION()
	void DealDamage(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
