// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CookingGameInstance.h"
#include "InteractableIngredient.generated.h"

UCLASS()
class BOTWSTYLECOOKING_API AInteractableIngredient : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractableIngredient();

	// get or set method for this objects collider
	void EnableCollision();
	void DisableCollision();

	void SetMoveSpeed(float value, const FVector& direction);

	UFUNCTION(BlueprintCallable)
	FIngredient GetIngredient();

	UFUNCTION(BlueprintCallable)
		void SetIngredient(FIngredient Ing);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveObjectToPosition();

	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* ObjectMovementComp;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere)
		FIngredient Ingredient;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool RandomIngredientOnStart = false;
	
};
