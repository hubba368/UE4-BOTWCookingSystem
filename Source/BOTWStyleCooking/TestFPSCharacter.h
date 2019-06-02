// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestFPSCharacter.generated.h"

UCLASS()
class BOTWSTYLECOOKING_API ATestFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestFPSCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);

	bool PlayerInCookingTrigger = false;

	void SetNearestValidCookingPot(class ACookingPot* Pot);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void PlayerForwardMovement(float Value);
	UFUNCTION()
		void PlayerSideMovement(float Value);

	void PlayerPickUpItem();

	void PlayerThrowItem();

	UPROPERTY(BlueprintReadOnly)
		bool PlayerIsHoldingItem = false;

	void PlayerCookItem();
	
private:
	UPROPERTY(EditAnywhere)
		class UCameraComponent* CameraComp;							
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* PlayerMeshComp;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* InteractablePositionComp;
	UPROPERTY(EditAnywhere)
		class UCharacterMovementComponent* MovementComp;
	UPROPERTY(EditAnywhere)
		class UCapsuleComponent* PlayerCollisionComp;

	class AActor* CanPlayerPickUpInteractableObj();

	class ACookingPot* NearestCookingPot;
};
