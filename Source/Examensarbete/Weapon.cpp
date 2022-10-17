// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "GameFramework/Actor.h"
#include "components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	RootComponent = WeaponMesh;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLocation -> SetupAttachment(WeaponMesh);
	MuzzleLocation -> SetWorldRotation(FRotator(0.f,90.f,0.f));

	Damage = 25.f;
	Offset = FVector::Zero();
	FireRate = 0.3f;
	ProjectileMaxFireDist = 10000.f;
	CanShoot = true;
	AddActorToIgnoreList(this);
}

USkeletalMeshComponent* AWeapon::GetMesh() const
{
	return WeaponMesh;
}

FHitResult AWeapon::GetHitResult() const
{
	return HitResult;
}

void AWeapon::AddActorToIgnoreList(const AActor* Actor)
{
	HitParams.AddIgnoredActor(Actor);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	//Setup for muzzle location
}



// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector EndPoint
	{
		MuzzleLocation -> GetComponentLocation()
		+ MuzzleLocation->GetComponentRotation().Vector()
		* ProjectileMaxFireDist
	};
	bool DidHit
	{
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			MuzzleLocation -> GetComponentLocation(),
			EndPoint,
			ECC_Visibility,
			HitParams
		)
	};

	if (!DidHit)
	{
		HitActor = nullptr;
	}
	else
	{
		HitActor = HitResult.GetActor();
	}
}

void AWeapon::Shoot()
{
	const UWorld* World { GetWorld() };

	if (!World || !CanShoot) return;

	CanShoot = false;

	World -> GetTimerManager().SetTimer(
		*ShootCooldownEndHandle,
		this,
		&AWeapon::OnShootCooldownEnd,
		FireRate,
		true);

	if (!HitActor) return;

	FPointDamageEvent PointDamage;
	PointDamage.HitInfo = HitResult;
	PointDamage.ShotDirection = MuzzleLocation->GetComponentRotation().Vector();
	PointDamage.Damage = Damage;

	// HitActor->TakeDamage(
	// 	PointDamage.Damage,
	// 	PointDamage,
	// 	Instigator ->Controller,
	// 	this);
}

void AWeapon::OnShootCooldownEnd()
{
	CanShoot = true;

	// Clear timer to avoid continuous calls.
	if (GetWorld ())
	{
		GetWorld ()->GetTimerManager ().ClearTimer (*ShootCooldownEndHandle);
	}
}
