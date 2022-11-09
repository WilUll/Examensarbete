// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                  AController* InstigateBy, AActor* DamageCauser)
{
	if (Damage <= 0) return;
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0.0f)
	{
		OnActorDeath.Broadcast();
		//Death();
		return;
	}
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::Heal(float HealAmount)
{
	if (CurrentHealth >= MaxHealth) return;

	CurrentHealth += HealAmount;

	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
}

void UHealthComponent::RegenHealth()
{
}

void UHealthComponent::Death()
{
	if (GetOwner() != nullptr && !GetOwner()->GetInstigatorController()->IsPlayerController())
	{
		USkeletalMeshComponent* SkeletalMeshComp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
		UCapsuleComponent* CapsuleComp = GetOwner()->FindComponentByClass<UCapsuleComponent>();
		if (SkeletalMeshComp != nullptr && CapsuleComp != nullptr)
		{
			CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			SkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			SkeletalMeshComp->SetSimulatePhysics(true);
		}
	}
}

float UHealthComponent::GetHealth() const
{
	return MaxHealth;
}

float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}
