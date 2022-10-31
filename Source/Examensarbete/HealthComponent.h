// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXAMENSARBETE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *InstigateBy, AActor * DamageCauser);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Heal(float HealAmount);

private:
	bool IsDead;
	
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;
	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	bool CanRegen;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float RegenerateHealthAmount;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float RegenerateAfterTime;
	float CurrentRegenerationTime;
	
	FTimerHandle TimerHandle_RegenTime;

	void RegenHealth();

	void Death();
public:
	UFUNCTION(BlueprintGetter)
	float GetHealth() const;
	
	UFUNCTION(BlueprintGetter)
	float GetCurrentHealth() const;

};
