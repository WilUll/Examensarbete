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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	int32 MaxReserve;



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float DamageAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float FireSpread;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float Range;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	USceneComponent* MuzzleLocation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FTimerHandle TimerHandle_FireRate;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName Socket;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimSequence* IdleAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimSequence* EquipAnimation;
	
	float LastFireTime;

	void Fire();

	//SOUNDS
	UPROPERTY (EditAnywhere,BlueprintReadWrite, Category = "Sounds")
	USoundBase* ShootSound;

	UPROPERTY (EditAnywhere,BlueprintReadWrite, Category = "Sounds")
	USoundBase* ReloadSound;

	UPROPERTY (EditAnywhere,BlueprintReadWrite, Category = "Sounds")
	USoundBase* MagEmptySound;

	UPROPERTY (EditAnywhere,BlueprintReadWrite, Category = "Sounds")
	USoundBase* NoAmmoSound;

	UPROPERTY (EditAnywhere,BlueprintReadWrite, Category = "Sounds")
	USoundBase* HitSound;

	UPROPERTY (EditAnywhere,BlueprintReadWrite, Category = "Combat")
	UMaterial* HitDecal;
public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EndFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Reload();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetWeaponInSocket(USceneComponent* Parent);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	UAnimationAsset* GetEquipAnim();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	UAnimationAsset* GetIdleAnim();

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentReserve;
	
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	bool UnlimitedAmmo;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	bool SingleFire;	
};
