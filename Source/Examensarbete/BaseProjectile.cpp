// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
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

	UE_LOG(LogTemp, Display, TEXT("IN HIT FUNC"))
	if (OtherActor != this)
	{
		UE_LOG(LogTemp, Display, TEXT("HIT ACTOR: %s"), Hit.GetActor())
		UGameplayStatics::ApplyDamage(OtherActor,
			Damage,
			UGameplayStatics::GetPlayerController(GetWorld(), 0),
			UGameplayStatics::GetPlayerPawn(GetWorld(), 0),
			UDamageType::StaticClass()
			);
		FString BoneName;
		Hit.BoneName.AppendString(BoneName);
		
		if (BoneName.ToLower() == "head")
		{
			UGameplayStatics::ApplyDamage(OtherActor,
									  Damage * 2,
									  UGameplayStatics::GetPlayerController(GetWorld(), 0),
									  UGameplayStatics::GetPlayerPawn(GetWorld(), 0),
									  UDamageType::StaticClass());
		}
		else
		{
			UGameplayStatics::ApplyDamage(OtherActor,
									  Damage,
									  UGameplayStatics::GetPlayerController(GetWorld(), 0),
									  UGameplayStatics::GetPlayerPawn(GetWorld(), 0),
									  UDamageType::StaticClass());
		}
	}

	Destroy();
}

