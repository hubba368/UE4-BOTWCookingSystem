// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableCookedProduct.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/GameEngine.h"
#include "Components/BoxComponent.h"

// Sets default values
AInteractableCookedProduct::AInteractableCookedProduct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ObjectMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ObjectMoveComp"));
	ObjectMovementComp->InitialSpeed = 0.0f;
	ObjectMovementComp->MaxSpeed = 50.0f;
	ObjectMovementComp->ProjectileGravityScale = 0.0f;
	ObjectMovementComp->bRotationFollowsVelocity = true;
	ObjectMovementComp->bShouldBounce = false;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;

	UStaticMeshComponent* SMesh = Cast<UStaticMeshComponent>(CollisionComp->GetChildComponent(0));
	//UE_LOG(LogTemp, Warning, TEXT("%d"),RootComponent->GetNumChildrenComponents());
	if (SMesh != NULL) {
		CollisionComp->SetBoxExtent(SMesh->Bounds.BoxExtent);
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("mesh is null"));
	}


}

void AInteractableCookedProduct::SetMoveSpeed(float value, const FVector & direction)
{
	ObjectMovementComp->InitialSpeed = 1000.0f;
	ObjectMovementComp->ProjectileGravityScale = 1.0f;
	ObjectMovementComp->Velocity = direction * ObjectMovementComp->InitialSpeed;
}

FCookedProduct AInteractableCookedProduct::GetProduct()
{
	return Product;
}

void AInteractableCookedProduct::SetProduct(FCookedProduct Ing)
{
	Product = Ing;
}

// Called when the game starts or when spawned
void AInteractableCookedProduct::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableCookedProduct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

