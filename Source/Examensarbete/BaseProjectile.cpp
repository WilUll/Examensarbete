// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    if (!CollisionComponent)
    {
	    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

    	CollisionComponent->InitSphereRadius(15.0f);

    	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

    	//Setup delegate
    	CollisionComponent->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
    	
    	RootComponent = CollisionComponent;
    }

	//Projectile movement
    if (!ProjectileMovementComponent)
    {
	    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

    	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);

    	ProjectileMovementComponent->InitialSpeed = 3000.f;

    	ProjectileMovementComponent->MaxSpeed = 3000.f;

    	ProjectileMovementComponent-> bRotationFollowsVelocity = true;

    	ProjectileMovementComponent-> bShouldBounce = false;

    	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
    }

	//Projectile mesh creation
	if(!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}

	//Delete bullet after 5 seconds
	InitialLifeSpan = 5.0f;


}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}

	Destroy();
}

