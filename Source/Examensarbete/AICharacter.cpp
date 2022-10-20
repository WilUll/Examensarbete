// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RAttackCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("R Attack Collider"));
	RAttackCollider->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("weapon_rSocket"));

	LAttackCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("L Attack Collider"));
	LAttackCollider->SetupAttachment(GetMesh(),  TEXT("weapon_lSocket"));

	
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAICharacter::Attack()
{
	
}
