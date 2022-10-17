// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100.f;
	HealthRegenPerSecond = 10.f;
	TimeToStartRegen = 3.f;
	CanRegen = false;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(CanRegen);

	CurrentHealth = MaxHealth;
	TimeLeftForRegen = 0.f;

	checkf(
		(TimeToStartRegen > 0.f) &&
		(MaxHealth > 0.f) &&
		(HealthRegenPerSecond >= 0.f),
		TEXT("ERROR: Invalid parameter at the Life Component from %s"),
		*GetOwner()->GetName());
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentHealth < MaxHealth || TimeLeftForRegen > 0.f)
	{
		TimeLeftForRegen -= DeltaTime;

		if (TimeLeftForRegen > 0.f) return;

		CurrentHealth += HealthRegenPerSecond * DeltaTime;
		CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
	}
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetHealthRegeneratedPerSecond() const
{
	return HealthRegenPerSecond;
}

bool UHealthComponent::CanRegenerate() const
{
	return  CanRegen;
}

bool UHealthComponent::EnableRegeneration()
{
	CanRegen = true;
	SetComponentTickEnabled(true);
	return  CanRegen;
}

bool UHealthComponent::DisableRegeneration()
{
	CanRegen = false;
	SetComponentTickEnabled(false);
	return  CanRegen;
}

void UHealthComponent::Heal(const float HealAmount)
{
	if (CurrentHealth < MaxHealth)
	{
		CurrentHealth += HealAmount;
		CurrentHealth = FMath::Clamp(CurrentHealth,0.0f, MaxHealth);
	}
	
}

void UHealthComponent::Damage(const float DamageTaken)
{
	if (CurrentHealth <= 0.f) return;

	CurrentHealth -= DamageTaken;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);

	TimeLeftForRegen = TimeToStartRegen;
}

