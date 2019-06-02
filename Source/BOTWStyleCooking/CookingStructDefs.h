#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Templates/Tuple.h"
#include "CookingStructDefs.generated.h"


UENUM(BlueprintType)
enum class EFoodType : uint8 { Fruit, Vegetable, Meat, Fish, Mushroom, Spice };

UENUM(BlueprintType)
enum class EEffectType : uint8 { Base, Hearty, Energizing, Enduring, Fireproof, Chilly, Spicy, Electro, Hasty, Sneaky, Mighty, Tough };

USTRUCT(BlueprintType)
struct FIngredient
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredients")
		int ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredients")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredients")
		EFoodType FoodType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredients")
		EEffectType EffectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredients")
		float HealthRestore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredients")
		float StaminaRestore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredients")
		float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredients")
		float Potency;
};

USTRUCT(BlueprintType)
struct FCookedProduct
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CookedProduct")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CookedProduct")
		EEffectType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CookedProduct")
		float HealthRestore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredients")
		float StaminaRestore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CookedProduct")
		float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CookedProduct")
		float Potency;
};

USTRUCT(BlueprintType)
struct FSingularRecipeReq
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipes")
		bool RequirementMet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipes")
		int SingularRequirementID;
};

USTRUCT(BlueprintType)
struct FMultipleRecipeReq
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipes")
		bool RequirementMet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipes")
		TArray<int> MultiRequirementIDs;
};

USTRUCT(BlueprintType)
struct FRecipe : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipes")
		int RecipeID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipes")
		FString RecipeName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipes")
		TArray<FSingularRecipeReq> SingularRequirements;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipes")
		TArray<FMultipleRecipeReq> MultipleRequirements;
};

