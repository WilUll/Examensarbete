// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"

#include "HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RAttackCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("R Attack Collider"));
	RAttackCollider->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("weapon_rSocket"));

	LAttackCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("L Attack Collider"));
	LAttackCollider->SetupAttachment(GetMesh(),  TEXT("weapon_lSocket"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()-> bOrientRotationToMovement = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAICharacter::ToggleWeaponColliders(bool TrueOrFalse)
{
	if (TrueOrFalse)
	{
		RAttackCollider -> SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		LAttackCollider -> SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}
	else
	{
		RAttackCollider -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LAttackCollider -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAICharacter::Attack()
{
	ToggleWeaponColliders(true);
	
}
