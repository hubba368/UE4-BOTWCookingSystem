// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CookingGameInstance.h"
#include "InteractableCookedProduct.generated.h"

UCLASS()
class BOTWSTYLECOOKING_API AInteractableCookedProduct : public AActor
{
	GENERATED_BODY()
	
public:
	AInteractableCookedProduct();



	void SetMoveSpeed(float value, const FVector& direction);

	UFUNCTION(BlueprintCallable)
		FCookedProduct GetProduct();

	UFUNCTION(BlueprintCallable)
		void SetProduct(FCookedProduct Ing);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* ObjectMovementComp;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere)
		FCookedProduct Product;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
};
