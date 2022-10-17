// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class EXAMENSARBETE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	/* Returns the skeletal mesh of the weapon */
	USkeletalMeshComponent* GetMesh() const;

	/* Returns the hit result of the weapon */
	FHitResult GetHitResult() const;

	/* Adds an actor to ignore to the hit params. */
	void AddActorToIgnoreList(const AActor* Actor);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	 * If the weapon can shoot, apply damage and reports a noise at the 
	 * muzzle location. If HitActor is not null, it will also apply hit sound,
	 * report a noise at the hit location and damage the actor.
	 */
	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Sets can shoot to true */
	virtual void OnShootCooldownEnd();

	/* Weapon Mesh */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* WeaponMesh;

	/* World location of the muzzle	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
	USceneComponent* MuzzleLocation;

	/* Damage done by the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float Damage;

	/* Gun muzzle's offset from the characters location. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector Offset;

	/* Fire rate of the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float FireRate;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float ProjectileMaxFireDist;

	/* Hit result to know where weapon is aiming */ 
	FHitResult HitResult;
	
	/* Hit params from HitResult */ 
	FCollisionQueryParams HitParams;
	
	/* Pointer to HitResult Actor */ 
	AActor* HitActor;
	
	/* Used to know if we can shoot */ 
	bool CanShoot;
	
	/* Timer to call OnShootCooldownEnd() when the cooldown ends */ 
	FTimerHandle* ShootCooldownEndHandle;
};
