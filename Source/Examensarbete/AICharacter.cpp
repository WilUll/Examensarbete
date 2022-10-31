// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"

#include "HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAICharacter::AAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RAttackCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("R Attack Collider"));
	RAttackCollider->SetupAttachment(GetMesh(), TEXT("weapon_rSocket"));
	RAttackCollider->SetCollisionProfileName(FName("OverlapAll"));
	RAttackCollider->MoveIgnoreActors.Add(this);
	RAttackCollider->OnComponentBeginOverlap.AddDynamic(this, &AAICharacter::DealDamage);
	RAttackCollider->SetNotifyRigidBodyCollision(true);

	LAttackCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("L Attack Collider"));
	LAttackCollider->SetupAttachment(GetMesh(), TEXT("weapon_lSocket"));
	LAttackCollider->SetCollisionProfileName(FName("OverlapAll"));
	LAttackCollider->MoveIgnoreActors.Add(this);
	LAttackCollider->OnComponentBeginOverlap.AddDynamic(this, &AAICharacter::DealDamage);
	LAttackCollider->SetNotifyRigidBodyCollision(true);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	ToggleWeaponColliders(false);
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AAICharacter::ToggleWeaponColliders(bool TrueOrFalse) const
{
	if (TrueOrFalse)
	{
		RAttackCollider->SetCollisionProfileName(TEXT("OverlapAll"));
		LAttackCollider->SetCollisionProfileName(TEXT("OverlapAll"));
	}
	else
	{
		RAttackCollider->SetCollisionProfileName(TEXT("NoCollision"));
		LAttackCollider->SetCollisionProfileName(TEXT("NoCollision"));
	}
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAICharacter::AttackStart()
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Red, "Attacking");
	ToggleWeaponColliders(true);
}

void AAICharacter::AttackEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Red, "StopAttack");
	ToggleWeaponColliders(false);
}

void AAICharacter::DealDamage(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor == PlayerPawn)
		{
			UGameplayStatics::ApplyDamage(OtherActor,
			                              DamageAmount,
			                              this->GetInstigatorController(),
			                              this,
			                              UDamageType::StaticClass());
		}
		GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Cyan, "HitPlayer");
	}
}
