// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

#include "HealthComponent.h"
#include "Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Player");

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FirstPersonCamera->SetupAttachment(RootComponent);
	FirstPersonCamera->bUsePawnControlRotation = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	FirstPersonCamera->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("head"));

	WeaponInt = 0;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < WeaponClass.Num(); i++)
	{
		Weapon.Add(GetWorld()->SpawnActor<AWeapon>(WeaponClass[i]));
		Weapon[i]->SetWeaponInSocket(GetMesh());
		Weapon[i]->SetOwner(this);
		Weapon[i]->SetActorHiddenInGame(true);
	}

	Weapon[WeaponInt]->SetActorHiddenInGame(false);
	GetMesh()->SetAnimation(Weapon[WeaponInt]->GetIdleAnim());

	APlayerController* PlayerController{
		GetWorld()->GetFirstPlayerController()
	};

	PlayerController->PlayerCameraManager->ViewPitchMax = 30.f;
	PlayerController->PlayerCameraManager->ViewPitchMin = -35.f;
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent)

	//Movement
	PlayerInputComponent->BindAxis(
		"MoveForward",
		this,
		&AFPSCharacter::MoveForward);

	PlayerInputComponent->BindAxis(
		"MoveRight",
		this,
		&AFPSCharacter::MoveRight
	);

	//Camera
	PlayerInputComponent->BindAxis(
		"MoveCamera",
		this,
		&AFPSCharacter::MoveCamera
	);

	PlayerInputComponent->BindAxis(
		"TurnPlayer",
		this,
		&AFPSCharacter::TurnPlayer
	);

	PlayerInputComponent->BindAction(
		"Sprint",
		IE_Pressed,
		this,
		&AFPSCharacter::Sprint
	);

	PlayerInputComponent->BindAction(
		"Sprint",
		IE_Released,
		this,
		&AFPSCharacter::StopSprinting
	);

	PlayerInputComponent->BindAction(
		"Shoot",
		IE_Pressed,
		this,
		&AFPSCharacter::Shoot
	);
	PlayerInputComponent->BindAction(
		"Shoot",
		IE_Released,
		this,
		&AFPSCharacter::StopShooting
	);
	PlayerInputComponent->BindAxis(
		"ChangeWeapon",
		this,
		&AFPSCharacter::ChangeWeapon
	);
	PlayerInputComponent->BindAction(
		"Reload",
		IE_Pressed,
		this,
		&AFPSCharacter::Reload
	);
	PlayerInputComponent->BindAction(
		"Jump",
		IE_Pressed,
		this,
		&AFPSCharacter::StartJump
	);
}

void AFPSCharacter::StartJump()
{
	Jump();
}

void AFPSCharacter::StopJump()
{
	StopJumping();
}


void AFPSCharacter::MoveForward(const float value)
{
	if (value != 0.0f) AddMovementInput(GetActorForwardVector(), value);
}

void AFPSCharacter::MoveRight(const float value)
{
	if (value != 0.0f) AddMovementInput(GetActorRightVector(), value);
}

void AFPSCharacter::TurnPlayer(const float value)
{
	AddControllerYawInput(
		TurnRate * value * GetWorld()->GetDeltaSeconds());
}

void AFPSCharacter::MoveCamera(const float value)
{
	AddControllerPitchInput(
		CameraMoveRate * value * GetWorld()->GetDeltaSeconds());

}

void AFPSCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 900.f;
}

void AFPSCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

UHealthComponent* AFPSCharacter::GetHealthComponent()
{
	return HealthComponent;
}

void AFPSCharacter::Shoot()
{
	Weapon[WeaponInt]->StartFire();
}

void AFPSCharacter::StopShooting()
{
	Weapon[WeaponInt]->EndFire();
}

void AFPSCharacter::ChangeWeapon(float Amount)
{
	
	Weapon[WeaponInt]->SetActorHiddenInGame(true);
	
	WeaponInt += Amount;
	WeaponInt = FMath::Clamp(WeaponInt, 0, Weapon.Num() - 1);
	
	Weapon[WeaponInt]->SetActorHiddenInGame(false);
}

void AFPSCharacter::Reload()
{
	Weapon[WeaponInt]->Reload();
}