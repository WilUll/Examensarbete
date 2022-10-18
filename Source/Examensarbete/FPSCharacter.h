// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

class AWeapon;
UCLASS(Abstract)
class EXAMENSARBETE_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(const float value);

	void MoveRight(const float value);

	void TurnPlayer(const float value);
	
	void MoveCamera(const float value);

	void Sprint();

	void StopSprinting();

	void Shoot();

	void StopShooting();

	UPROPERTY(EditAnywhere, Category = "Camera")
	float TurnRate;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraMoveRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UCameraComponent* FirstPersonCamera;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY()
	AWeapon* Weapon;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
