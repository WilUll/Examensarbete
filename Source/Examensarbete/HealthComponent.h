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
	
	/* Returns max health */
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	/* Returns current health */
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	/* Returns health regenerated per second */
	UFUNCTION(BlueprintCallable)
	float GetHealthRegeneratedPerSecond() const;

	/* Returns if the Actor can regenerate */
	UFUNCTION(BlueprintCallable)
	bool CanRegenerate() const;

	/* Enables regeneration */
	UFUNCTION(BlueprintCallable)
	bool EnableRegeneration();
	
	/* Disables regeneration */
	UFUNCTION(BlueprintCallable)
	bool DisableRegeneration();

	UFUNCTION(BlueprintCallable)
	void Heal(const float HealAmount);
	
	UFUNCTION(BlueprintCallable)
	void Damage(const float DamageTaken);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float HealthRegenPerSecond;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float TimeToStartRegen;

	float TimeLeftForRegen;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	bool CanRegen;
};
