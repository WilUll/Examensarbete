// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBase.h"

#include "Components/BoxComponent.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	PickupCollider -> SetupAttachment(RootComponent);

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	PickupMesh -> SetupAttachment(PickupMesh);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupBase::OnPickup()
{
	 
}

