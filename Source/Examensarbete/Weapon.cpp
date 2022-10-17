// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLocation->SetupAttachment(WeaponMesh);

	MaxAmmo = 32;
	MaxReserve = 248;
	FireRate = 0.2f;
	DamageAmount = 25.f;
	Range = 2000.f;
	FireSpread = 2.f;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;
	CurrentReserve = MaxReserve;
}

void AWeapon::Fire()
{
	AActor* MyOwner = GetOwner();

	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner -> GetActorEyesViewPoint(EyeLocation,EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();

		//BulletSpread
		float HalfRad = FMath::DegreesToRadians(FireSpread);
		ShotDirection = FMath::VRandCone(ShotDirection,HalfRad,HalfRad);

		FVector TraceEnd = EyeLocation + (ShotDirection * Range);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FVector TracerEndPoint = TraceEnd;

		if (CurrentAmmo > 0 )
		{
			CurrentAmmo -= 1;

			DrawDebugLine(
				GetWorld(),
				EyeLocation,
				TraceEnd,
				FColor::Red,
				false,
				2.f
			);

			FHitResult Hit;
			if (GetWorld()->LineTraceSingleByChannel(Hit,
				EyeLocation, TraceEnd, ECC_GameTraceChannel1, QueryParams))
			{
				AActor* HitActor = Hit.GetActor();


				UGameplayStatics::ApplyDamage(HitActor,
					DamageAmount,
					MyOwner->GetInstigatorController(),
					MyOwner,
					UDamageType::StaticClass());
			}

			LastFireTime = GetWorld()->TimeSeconds;
		}
		else
		{
			Reload();
		}
	}
}

void AWeapon::StartFire()
{
	float FirstDelay = FMath::Max(LastFireTime + FireRate - GetWorld()->TimeSeconds, 0.0f);
	GetWorldTimerManager().SetTimer(TimerHandle_FireRate, this, &AWeapon::Fire, FireRate,true, FirstDelay);
}

void AWeapon::EndFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_FireRate);
}

void AWeapon::Reload()
{
	int32 AmmoDiffrence = MaxAmmo - CurrentAmmo;

	if (CurrentAmmo == 0 && CurrentReserve == 0)
	{
		
	}

	if (CurrentAmmo >= 0 && CurrentAmmo < MaxAmmo)
	{
		if (CurrentReserve <= AmmoDiffrence)
		{
			CurrentAmmo += CurrentReserve;
			CurrentReserve -= AmmoDiffrence;
		}
		else 
		{
			CurrentAmmo += AmmoDiffrence;
			CurrentReserve -= AmmoDiffrence;
		}
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

