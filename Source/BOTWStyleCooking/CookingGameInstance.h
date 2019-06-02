// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "CookingStructDefs.h"
#include "CookingGameInstance.generated.h"





UCLASS()
class BOTWSTYLECOOKING_API UCookingGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCookingGameInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	FIngredient SelectSingleIngredient();

	UFUNCTION(BlueprintCallable)
	FIngredient SelectSingleSpecificIngredient(FString IngName);

protected:
	
private:

	void InitAllIngredients();

	TArray<FIngredient> BaseIngredients;
	TArray<FIngredient> HeartyIngredients;
	TArray<FIngredient> EnergizingIngredients;
	TArray<FIngredient> EnduringIngredients;
	TArray<FIngredient> FireproofIngredients;
	TArray<FIngredient> ChillyIngredients;
	TArray<FIngredient> SpicyIngredients;
	TArray<FIngredient> ElectroIngredients;
	TArray<FIngredient> HastyIngredients;
	TArray<FIngredient> SneakyIngredients;
	TArray<FIngredient> MightyIngredients;
	TArray<FIngredient> ToughIngredients;

	TArray <TArray<FIngredient>> AllIngredients;

};
