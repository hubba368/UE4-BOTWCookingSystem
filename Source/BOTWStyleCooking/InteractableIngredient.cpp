// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableIngredient.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/GameEngine.h"
#include "Components/BoxComponent.h"


// Sets default values
AInteractableIngredient::AInteractableIngredient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ObjectMovementComp = Cast<UProjectileMovementComponent>(GetComponentByClass(UProjectileMovementComponent::StaticClass()));
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

void AInteractableIngredient::EnableCollision()
{
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
void AInteractableIngredient::DisableCollision()
{
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AInteractableIngredient::SetMoveSpeed(float value, const FVector& direction)
{
	ObjectMovementComp->InitialSpeed = 1000.0f;
	ObjectMovementComp->ProjectileGravityScale = 1.0f;
	ObjectMovementComp->Velocity = direction * ObjectMovementComp->InitialSpeed;
}


void AInteractableIngredient::SetIngredient(FIngredient Ing)
{
	Ingredient = Ing;
}

// Called when the game starts or when spawned
void AInteractableIngredient::BeginPlay()
{
	Super::BeginPlay();
	// assign an ingredient to actor
	//Ingredient = Cast<UCookingGameInstance>(GetGameInstance())->SelectSingleIngredient();
	
}

FIngredient AInteractableIngredient::GetIngredient()
{
	return Ingredient;
}

void AInteractableIngredient::MoveObjectToPosition()
{

}

// Called every frame
void AInteractableIngredient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

