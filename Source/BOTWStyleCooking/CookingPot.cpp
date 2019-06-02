// Fill out your copyright notice in the Description page of Project Settings.

#include "CookingPot.h"
#include "InteractableIngredient.h"
#include "Components/BoxComponent.h"
#include "Engine/GameEngine.h"
#include "ConstructorHelpers.h"
#include "TestFPSCharacter.h"

// Sets default values
ACookingPot::ACookingPot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	InteractTriggerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractTrigger"));

	// init recipe data table // 
	static ConstructorHelpers::FObjectFinder<UDataTable> temp(TEXT("DataTable'/Game/RecipeDataTable.RecipeDataTable'"));
	RecipeList = temp.Object;
}

int ACookingPot::RankIngredientByEffect(FIngredient Ing)
{
	int Rank = 0;
	switch (Ing.EffectType)
	{
	case EEffectType::Base:
		Rank = 1;
		break;
	case EEffectType::Hearty:
		Rank = 2;
		break;
	case EEffectType::Energizing:
		Rank = 3;
		break;
	case EEffectType::Enduring:
		Rank = 4;
		break;
	case EEffectType::Fireproof:
		Rank = 5;
		break;
	case EEffectType::Chilly:
		Rank = 6;
		break;
	case EEffectType::Spicy:
		Rank = 7;
		break;
	case EEffectType::Electro:
		Rank = 8;
		break;
	case EEffectType::Hasty:
		Rank = 9;
		break;
	case EEffectType::Sneaky:
		Rank = 10;
		break;
	case EEffectType::Mighty:
		Rank = 11;
		break;
	case EEffectType::Tough:
		Rank = 12;
		break;
	}
	return Rank;
}

int ACookingPot::RankIngredientByFoodType(FIngredient Ing)
{
	int Rank = 0;
	switch (Ing.FoodType)
	{
	case EFoodType::Fruit:
		Rank = 1;
		break;
	case EFoodType::Meat:
		Rank = 2;
		break;
	case EFoodType::Mushroom:
		Rank = 3;
		break;
	case EFoodType::Vegetable:
		Rank = 4;
		break;
	case EFoodType::Spice:
		Rank = 5;
		break;
	}
	return Rank;
}

FString ACookingPot::GetFoodTypeString(FIngredient Ing)
{
	FString FType = "";
	switch (Ing.FoodType)
	{
	case EFoodType::Fruit:
		FType = "Fruit";
		break;
	case EFoodType::Meat:
		FType = "Meat";
		break;
	case EFoodType::Mushroom:
		FType = "Mushroom";
		break;
	case EFoodType::Vegetable:
		FType = "Vegetable";
		break;
	case EFoodType::Spice:
		FType = "";
		break;
	}
	return FType;
}

FString ACookingPot::GetEffectTypeStringByIngredient(FIngredient Ing)
{
	FString EffectName = "";
	switch (Ing.EffectType)
	{
	case EEffectType::Base:
		EffectName = "";
		break;
	case EEffectType::Hearty:
		EffectName = "Hearty";
		break;
	case EEffectType::Energizing:
		EffectName = "Energizing";
		break;
	case EEffectType::Enduring:
		EffectName = "Enduring";
		break;
	case EEffectType::Fireproof:
		EffectName = "Fireproof";
		break;
	case EEffectType::Chilly:
		EffectName = "Chilly";
		break;
	case EEffectType::Spicy:
		EffectName = "Spicy";
		break;
	case EEffectType::Electro:
		EffectName = "Electro";
		break;
	case EEffectType::Hasty:
		EffectName = "Hasty";
		break;
	case EEffectType::Sneaky:
		EffectName = "Sneaky";
		break;
	case EEffectType::Mighty:
		EffectName = "Mighty";
		break;
	case EEffectType::Tough:
		EffectName = "Tough";
		break;
	}
	return EffectName;
}

FString ACookingPot::GetEffectTypeStringByType(EEffectType EType)
{
	FString EffectName = "";
	switch (EType)
	{
	case EEffectType::Base:
		break;
	case EEffectType::Hearty:
		EffectName = "Hearty";
		break;
	case EEffectType::Energizing:
		EffectName = "Energizing";
		break;
	case EEffectType::Enduring:
		EffectName = "Enduring";
		break;
	case EEffectType::Fireproof:
		EffectName = "Fireproof";
		break;
	case EEffectType::Chilly:
		EffectName = "Chilly";
		break;
	case EEffectType::Spicy:
		EffectName = "Spicy";
		break;
	case EEffectType::Electro:
		EffectName = "Electro";
		break;
	case EEffectType::Hasty:
		EffectName = "Hasty";
		break;
	case EEffectType::Sneaky:
		EffectName = "Sneaky";
		break;
	case EEffectType::Mighty:
		EffectName = "Mighty";
		break;
	case EEffectType::Tough:
		EffectName = "Tough";
		break;
	}
	return EffectName;
}

// Called when the game starts or when spawned
void ACookingPot::BeginPlay()
{
	Super::BeginPlay();
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACookingPot::OnOverlapBegin);
	CollisionComp->SetGenerateOverlapEvents(true);

	InteractTriggerComp->OnComponentBeginOverlap.AddDynamic(this, &ACookingPot::OnOverlapBeginTrigger);
	InteractTriggerComp->SetGenerateOverlapEvents(true);
}

// Called every frame
void ACookingPot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ACookingPot::CheckValidSingularReq(TArray<FIngredient> IngList, FRecipe* CurRec)
{
	// if a TMap was used to store the ingredient list, would have to use the map key as the ID in the recipe struct
	int IngCount = 0;
	// check single item requirements
	for (int j = 0; j < IngList.Num(); j++)
	{
		for (int i = 0; i < CurRec->SingularRequirements.Num(); i++)
		{
			if (IngList[j].ID == CurRec->SingularRequirements[i].SingularRequirementID && !CurRec->SingularRequirements[i].RequirementMet)
			{			
				IngCount++;
				CurRec->SingularRequirements[i].RequirementMet = true;
			}
		}
	}
	return IngCount;
}

int ACookingPot::CheckValidMultiReq(TArray<FIngredient> IngList, FRecipe* CurRec)
{
	int IngCount = 0;
	for (int i = 0; i < CurRec->MultipleRequirements.Num(); i++)
	{
		for (int j = 0; j < IngList.Num(); j++)
		{
			for (int k = 0; k < CurRec->MultipleRequirements[i].MultiRequirementIDs.Num(); k++)
			{
				if (IngList[j].ID == CurRec->MultipleRequirements[i].MultiRequirementIDs[k] && !CurRec->MultipleRequirements[i].RequirementMet)
				{
					IngCount++;
					CurRec->MultipleRequirements[i].RequirementMet = true;
				}
			}
		}
	}
	return IngCount;
}

// generates the product name based on the recipe that has been chosen, based on the input ingredients.
FString ACookingPot::GenerateNewProductName(TArray<FIngredient> IngList)
{
	FString ResultName = "";
	bool RecipeHasMultipleIngReq = false;
	int NumOfRequiredSingleIngs = 0;
	int NumOfRequiredMultiIngs = 0;

	TArray<FRecipe*> SelectedValidRecipes;

	if (RecipeList != nullptr)
	{
		for (auto& iter : RecipeList->RowMap)
		{
			FRecipe* CurRec = (FRecipe*)(iter.Value);
			NumOfRequiredSingleIngs = CurRec->SingularRequirements.Num();
			NumOfRequiredMultiIngs = CurRec->MultipleRequirements.Num() != 0 ? CurRec->MultipleRequirements.Num() : 0;

			int SingleIngCount = CheckValidSingularReq(IngList, CurRec);
			int MultiIngCount = 0;

			// we only need to check that atleast one multi req is met (per requirement)
			// e.g if recipe has 'any of fish' req then as long as that is met it will work
			if (NumOfRequiredMultiIngs != 0)
			{
				RecipeHasMultipleIngReq = true;				
				MultiIngCount = CheckValidMultiReq(IngList, CurRec);
			}

			if (SingleIngCount == NumOfRequiredSingleIngs && RecipeHasMultipleIngReq && MultiIngCount == NumOfRequiredMultiIngs)
			{// recipe with multiple choice ingredient req
				//UE_LOG(LogTemp, Warning, TEXT("multiple choice recipe got"));
				//UE_LOG(LogTemp, Warning, TEXT("Recipe ID: %d"), CurRec->RecipeID);
				SelectedValidRecipes.Add(CurRec);
			}
			else if (SingleIngCount == NumOfRequiredSingleIngs && !RecipeHasMultipleIngReq)
			{// regular recipe
				//UE_LOG(LogTemp, Warning, TEXT("Regular recipe got"));
				//UE_LOG(LogTemp, Warning, TEXT("Recipe ID: %d"), CurRec->RecipeID);
				SelectedValidRecipes.Add(CurRec);
			}

			RecipeHasMultipleIngReq = false;
		}

		// go back through and reset all bools
		// Todo: move this to previous loop
		for (auto& iter : RecipeList->RowMap) 
		{
			FRecipe* CurRec = (FRecipe*)(iter.Value);

			for (int i = 0; i < CurRec->SingularRequirements.Num(); i++)
			{
				CurRec->SingularRequirements[i].RequirementMet = false;
			}

			for (int j = 0; j < CurRec->MultipleRequirements.Num(); j++)
			{
				CurRec->MultipleRequirements[j].RequirementMet = false;
			}		
		}

		if (SelectedValidRecipes.Num() != 0)
		{
			SelectedValidRecipes.Sort([](const FRecipe& Lhs, const FRecipe& Rhs)
			{
				int LVal = Lhs.MultipleRequirements.Num() + Lhs.SingularRequirements.Num();
				int RVal = Rhs.MultipleRequirements.Num() + Rhs.SingularRequirements.Num();

				return LVal > RVal;
			});

			// afaik BOTW will select the recipe with the larger req list
			// e.g. bread requires rock salt and wheat, whilst meat/fish pie requires salt, wheat, and meat/fish
			FRecipe* SelectedRecipe = SelectedValidRecipes[0];
			ResultName = SelectedRecipe->RecipeName;
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("No recipe selected"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Datatable is empty"));
	}

	return ResultName;
}

// generates product stats and final product 
FCookedProduct ACookingPot::GenerateNewProduct(TArray<FIngredient> IngList, FString SelectedRecipeName)
{
	float HealthSum = 0.0f;
	float HeartyHealthSum = 0.0f;
	float StamSum = 0.0f;
	float DurationSum = 0.0f;
	float PotencySum = 0.0f;

	FString PotencyStr = "";
	FString ResultName = "";

	EEffectType SelectedType = EEffectType::Base;

	bool MixedBoosts = false;

	// swanky c++11 lambdas
	// sort to make it a bit easier to check for mixed boost ingredients
	IngList.Sort([this](const FIngredient& Lhs, const FIngredient& Rhs)
	{
		return (RankIngredientByEffect(Lhs) > RankIngredientByEffect(Rhs));
	});

	// stat formulae:
	// Health = sum of all health restore amounts x 2
	// Stamina = (1 ring = 4 sections) sum of stam restores ( or 0 if there are mixed boosts)
	// Duration = sum + 30 seconds for each ing added ( or 0 if there are mixed boosts)
	// potency = sum of all potency values checked against thresholds ( or 0 if there are mixed boosts)
	for (int i = 0; i < IngList.Num(); i++)
	{
		HealthSum += IngList[i].HealthRestore * 2;
		StamSum += IngList[i].StaminaRestore;
		DurationSum += IngList[i].Duration;
		DurationSum += 30.0f;
		PotencySum += IngList[i].Potency;

		if (IngList[i].EffectType == EEffectType::Hearty)
		{
			HeartyHealthSum += IngList[i].HealthRestore;
		}

		// last index checking
		if (IngList.IsValidIndex(i + 1))
		{
			if (RankIngredientByEffect(IngList[i]) != RankIngredientByEffect(IngList[i + 1]))
			{
				if (RankIngredientByEffect(IngList[i]) != 1 && RankIngredientByEffect(IngList[i + 1]) != 1)
				{
					UE_LOG(LogTemp, Warning, TEXT("Mixed boosts"));
					MixedBoosts = true;
				}
			}
		}
	}

	if (MixedBoosts)
	{
		PotencySum = 0.0f;
		DurationSum = 0.0f;
		StamSum = 0.0f;
	}
	else
	{
		for (FIngredient Ing : IngredientList)
		{
			if (Ing.EffectType != EEffectType::Base)
			{
				SelectedType = Ing.EffectType;
				break;
			}
		}
	}
	// calc potency
	if (PotencySum >= MaxPotencyThreshold)
	{
		PotencyStr = "Potent";
	}
	else if (PotencySum < MaxPotencyThreshold && PotencySum >= MidPotencyThreshold)
	{
		PotencyStr = "Stout";
	}

	// TODO add potencies to ingredients and add 'CookedProduct' Actor on finish
	
	ResultName += " " + PotencyStr + " " + GetEffectTypeStringByType(SelectedType) + " " + SelectedRecipeName;
	FCookedProduct NewProduct = { ResultName, SelectedType, HealthSum, StamSum, DurationSum, PotencySum };

	IngredientList.Empty();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, NewProduct.Name);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Health: %f"), NewProduct.HealthRestore));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Hearty Health: %f"), HeartyHealthSum));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Stamina Raw Val: %f"), NewProduct.StaminaRestore));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Stamina Ring(s) restored: %f, Ring(s) extra: %f"), NewProduct.StaminaRestore));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Duration: %f"), NewProduct.Duration));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Potency: %f"), NewProduct.Potency));
	ProductMade = true;
	FinalProduct = NewProduct;
	return NewProduct;
}

void ACookingPot::AddIngredientToPool(FIngredient Ing)
{
	if (IngredientList.Num() < 5)
	{		
		IngredientList.Add(Ing);	
	}
}

void ACookingPot::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (IngredientList.Num() < 5)
		{
			AInteractableIngredient* ingredient = Cast<AInteractableIngredient>(OtherActor);
			AddIngredientToPool(ingredient->GetIngredient());
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, ingredient->GetIngredient().Name);		
		}
		OtherActor->Destroy();
	}
}

void ACookingPot::OnOverlapBeginTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ATestFPSCharacter* Player = Cast<ATestFPSCharacter>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Cooking raedy"));
		Player->PlayerInCookingTrigger = true;
		Player->SetNearestValidCookingPot(this);
	}
}

FCookedProduct ACookingPot::GenerateCookedProduct()
{
	FString RecipeName = IngredientList.Num() > 0 ? GenerateNewProductName(IngredientList) : "";
	FCookedProduct Result = {};

	if (RecipeName == "")
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to create product."));
		return FCookedProduct{};
	}
	else 
	{
		Result = GenerateNewProduct(IngredientList, RecipeName);
		ProductMade = true;
	}

	return Result;
}
