// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpellProjectile::ASpellProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->MaxSpeed = InitialSpeed;
	ProjectileMovement -> InitialSpeed = InitialSpeed;
}

// Called when the game starts or when spawned
void ASpellProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh -> OnComponentHit.AddDynamic(this, &ASpellProjectile::OnHit);
}

// Called every frame
void ASpellProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpellProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr) return;

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		Destroy();
	}
}

