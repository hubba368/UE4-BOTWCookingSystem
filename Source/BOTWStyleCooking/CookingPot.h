// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CookingGameInstance.h"
#include "Engine/DataTable.h"
#include "CookingPot.generated.h"

UCLASS()
class BOTWSTYLECOOKING_API ACookingPot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACookingPot();

private:

	int RankIngredientByEffect(FIngredient Ing);

	int RankIngredientByFoodType(FIngredient Ing);

	FString GetFoodTypeString(FIngredient Ing);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FIngredient> IngredientList;

	UPROPERTY(EditAnywhere)
	int32 MaxIngredientNum = 5;
	
	UPROPERTY(EditAnywhere)
		float MaxPotencyThreshold = 45.0f;
	UPROPERTY(EditAnywhere)
		float MidPotencyThreshold = 30.0f;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* InteractTriggerComp;

	FString GenerateNewProductName(TArray<FIngredient> IngList);

	int CheckValidSingularReq(TArray<FIngredient> IngList, FRecipe* CurRec);

	int CheckValidMultiReq(TArray<FIngredient> IngList, FRecipe* CurRec);

	FCookedProduct GenerateNewProduct(TArray<FIngredient> IngList, FString SelectedRecipeName);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapBeginTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		FCookedProduct GenerateCookedProduct();
	
	UFUNCTION(BlueprintCallable)
		void AddIngredientToPool(FIngredient Ing);

	UFUNCTION(BlueprintCallable)
	FString GetEffectTypeStringByIngredient(FIngredient Ing);

	UFUNCTION(BlueprintCallable)
	FString GetEffectTypeStringByType(EEffectType EType);

	UDataTable* RecipeList;

	// for testing purposes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool ProductMade = false; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FCookedProduct FinalProduct;
};
