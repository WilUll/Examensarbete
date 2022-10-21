// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetLocked = false;
	NextAttackReady = false;
	Attacking = false;
	AttackDamaging = false;
	MovingForwards = false;
	MovingBackwards = false;
	RotateTowardsTarget = true;
	Stumbling = false;
	RotationSmoothing = 5.0f;
	LastRotationSpeed = 0.0f;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RotateTowardsTarget)
		LookAtSmooth();
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::Attack()
{
	Attacking = true;
	NextAttackReady = false;
	AttackDamaging = false;

	AttackHitActors.Empty();
}

void AEnemyBase::AttackLunge()
{
	if (Target != NULL)
	{
		FVector Direction = Target-> GetActorLocation() - GetActorLocation();
		Direction = FVector(Direction.X, Direction.Y, 0);
		FRotator Rotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		SetActorRotation(Rotation);
	}

	FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * 70);
	SetActorLocation(NewLocation, true);
}

void AEnemyBase::EndAttack()
{
	Attacking = false;
	NextAttackReady = false;
}

void AEnemyBase::SetAttackDamaging(bool Damaging)
{
	AttackDamaging = Damaging;
}

void AEnemyBase::SetMovingForwards(bool IsMovingForwards)
{
	MovingForwards = IsMovingForwards;
}

void AEnemyBase::SetMovingBackwards(bool IsMovingBackwards)
{
	MovingBackwards = IsMovingBackwards;
}

void AEnemyBase::EndStumble()
{
	Stumbling = false;
}

void AEnemyBase::AttackNextReady()
{
	NextAttackReady = true;
}

void AEnemyBase::LookAtSmooth()
{
	if (Target != NULL && TargetLocked &&
		!Attacking && !GetCharacterMovement()->IsFalling())
	{
		FVector Direction = Target -> GetActorLocation() - GetActorLocation();
		Direction = FVector(Direction.X, Direction.Y, 0);
		FRotator Rotation = FRotationMatrix::MakeFromX(Direction).Rotator();

		FRotator SmoothedRotation = FMath::Lerp(GetActorRotation(), Rotation, RotationSmoothing * GetWorld()->DeltaTimeSeconds);

		LastRotationSpeed = SmoothedRotation.Yaw - GetActorRotation().Yaw;

		SetActorRotation(SmoothedRotation);
	}
}

float AEnemyBase::GetCurrentRotationSpeed()
{
	if (RotateTowardsTarget)
		return LastRotationSpeed;

	return  0.0f;
}

