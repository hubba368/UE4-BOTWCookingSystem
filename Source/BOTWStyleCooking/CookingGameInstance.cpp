// Fill out your copyright notice in the Description page of Project Settings.

#include "CookingGameInstance.h"

UCookingGameInstance::UCookingGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InitAllIngredients();
}

FIngredient UCookingGameInstance::SelectSingleIngredient()
{
	int32 index = FMath::RandRange(0, AllIngredients.Num() - 1);
	TArray<FIngredient> temp = AllIngredients[index];
	int32 index2 = FMath::RandRange(0, temp.Num() - 1);
	return temp[index2];
}

FIngredient UCookingGameInstance::SelectSingleSpecificIngredient(FString IngName)
{// probs shouldve used a TMap instaed of TArray
	FIngredient Result = FIngredient{};
	if (AllIngredients.Num() > 0)
	{
		for (int i = 0; i < AllIngredients.Num(); i++)
		{
			TArray<FIngredient> temp = AllIngredients[i];

			if (temp.Num() > 0)
			{
				for (int j = 0; j < temp.Num(); j++)
				{
					if (temp[j].Name == IngName)
					{
						Result = temp[j];
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, Result.Name);

						return Result;
					}
				}
			}
		}
	}

	return Result;

}

// Should usually set up these in a Json file for datatable setup
void UCookingGameInstance::InitAllIngredients()
{
	// base ingredients (health restore)
	FIngredient Apple = { 1 ,"Apple", EFoodType::Fruit, EEffectType::Base, 0.5f, 0.0f, 0.0f, 0.0f };
	FIngredient RawMeat = { 2 ,"Meat" , EFoodType::Meat, EEffectType::Base, 1.0f, 0.0f, 0.0f, 0.0f };
	FIngredient RawGourmetMeat = { 3, "Gourmet Meat" , EFoodType::Meat, EEffectType::Base, 3.0f, 0.0f, 0.0f, 0.0f };
	FIngredient SankeCarp = { 4, "Sanke Carp" , EFoodType::Meat,  EEffectType::Base, 1.0f, 0.0f, 0.0f, 0.0f };
	FIngredient HyruleHerb = { 5, "Hyrule Herb" , EFoodType::Vegetable, EEffectType::Base, 1.0f, 0.0f, 0.0f, 0.0f };
	FIngredient PalmFruit = { 6, "Palm Fruit" , EFoodType::Fruit, EEffectType::Base, 1.0f, 0.0f, 0.0f, 0.0f };
	FIngredient Butter = { 7, "Butter" , EFoodType::Spice, EEffectType::Base, 0.5f, 0.0f, 50.0f, 0.0f };
	FIngredient Wheat = { 8, "Wheat" , EFoodType::Spice, EEffectType::Base, 0.5f, 0.0f, 30.0f, 0.0f };
	FIngredient Milk = { 9, "Milk" , EFoodType::Spice, EEffectType::Base, 0.5f, 0.0f, 50.0f, 0.0f };
	FIngredient Wildberry = { 10, "Wildberry" , EFoodType::Fruit, EEffectType::Base, 0.5f, 0.0f, 0.0f, 0.0f };
	FIngredient HylianShroom = { 11, "Hylian Shroom" , EFoodType::Mushroom, EEffectType::Base, 0.5f, 0.0f, 0.0f, 0.0f };
	FIngredient Salt = { 12, "Salt" , EFoodType::Spice, EEffectType::Base, 0.5f, 0.0f, 30.0f, 0.0f };
	FIngredient Acorn = { 13, "Acorn" , EFoodType::Spice, EEffectType::Base, 0.25f, 0.0f, 20.0f, 0.0f };
	FIngredient Fairy = { 14, "Fairy" , EFoodType::Spice, EEffectType::Base, 5.0f, 0.0f, 0.0f, 0.0f };

	// hearty ingredients (all health and extra health)
	FIngredient Truffle = { 15,"Truffle" , EFoodType::Mushroom, EEffectType::Hearty, 1.0f, 0.0f, 0.0f, 0.0f };
	FIngredient HeartyBass = { 16,"Hearty Bass" , EFoodType::Meat, EEffectType::Hearty, 2.0f, 0.0f, 0.0f, 0.0f };
	FIngredient HeartyDurian = { 17,"Hearty Durian" , EFoodType::Fruit, EEffectType::Hearty, 4.0f, 0.0f, 0.0f, 0.0f };
	FIngredient BigRadish = { 18,"Big Radish" , EFoodType::Vegetable, EEffectType::Hearty, 5.0f, 0.0f, 0.0f, 0.0f };
	FIngredient BlueshellSnail = {19, "Blueshell Snail" , EFoodType::Meat, EEffectType::Hearty, 3.0f, 0.0f, 0.0f, 0.0f };

	// enegizing (stamina restore) 1 ring = 4 parts
	FIngredient Stamella = { 20,"Stamella Shroom", EFoodType::Mushroom, EEffectType::Energizing, 1.0f, 0.25f, 0.0f, 0.0f };
	FIngredient BrightCrab = { 21,"Bright-Eyed Crab", EFoodType::Meat, EEffectType::Energizing, 2.0f, 0.5f, 0.0f, 0.0f };
	FIngredient BeeHoney = { 22,"Courser Bee Honey", EFoodType::Spice, EEffectType::Energizing, 5.0f, 0.5f,0.0f, 0.0f };
	FIngredient StaminokaBass = { 23,"Staminoka Bass", EFoodType::Meat, EEffectType::Energizing, 2.0f, 1.0f, 0.0f, 0.0f };

	// enduring (temp stamina boosts) 1 ring = 10 parts
	FIngredient EnduraShroom = { 24,"Endura Shroom", EFoodType::Mushroom, EEffectType::Enduring, 2.0f, 0.1f, 0.0f, 0.0f };
	FIngredient EnduraCarrot = { 25,"Endura Carrot", EFoodType::Vegetable, EEffectType::Enduring, 4.0f, 0.4f, 0.0f, 0.0f };

	//chilly (resist warm temps)
	FIngredient Hydromelon = { 26,"Hydromelon", EFoodType::Fruit, EEffectType::Chilly, 1.0f, 0.0f, 2.00f, 5.0f };
	FIngredient Chillshroom = { 27,"Chillshroom", EFoodType::Mushroom, EEffectType::Chilly, 1.0f, 0.0f, 2.00f, 10.0f };
	FIngredient ChillfinTrout = { 28,"Chillfin Trout", EFoodType::Meat, EEffectType::Chilly, 2.0f, 0.0f, 2.00f, 10.0f };
	FIngredient CoolSafflina = { 29,"Cool Safflina", EFoodType::Vegetable, EEffectType::Chilly, 0.0f, 0.0f, 2.00f, 5.0f };

	//spicy (resist cold temps)
	FIngredient SpicyPepper = { 30,"Spicy Pepper", EFoodType::Vegetable, EEffectType::Spicy, 1.0f, 0.0f, 2.00f, 5.0f };
	FIngredient Sunshroom = { 31,"Sunshroom", EFoodType::Mushroom, EEffectType::Spicy, 1.0f, 0.0f, 2.00f, 10.0f };
	FIngredient SizzlefinTrout = { 32,"Sizzlefin Trout", EFoodType::Meat, EEffectType::Spicy, 2.0f, 0.0f, 2.00f, 10.0f };

	//electro (resist electric attacks)
	FIngredient Voltfruit = {33, "Voltfruit", EFoodType::Fruit, EEffectType::Electro, 1.0f, 0.0f, 2.0f, 8.0f };
	FIngredient Zapshroom = { 34,"Zapshroom", EFoodType::Mushroom, EEffectType::Electro, 1.0f, 0.0f, 2.0f, 16.0f };
	FIngredient VoltfinTrout = { 35,"Voltfin Trout", EFoodType::Meat, EEffectType::Electro, 2.0f, 0.0f, 2.0f, 16.0f };

	//hasty (move speed increase)
	FIngredient Rushroom = { 36,"Rushroom", EFoodType::Mushroom, EEffectType::Hasty, 1.0f, 0.0f, 0.3f, 7.0f };
	FIngredient SwiftCarrot = { 37,"Swift Carrot", EFoodType::Vegetable, EEffectType::Hasty, 1.0f, 0.0f, 0.30f, 7.0f };
	FIngredient FleetLotus = { 38,"Fleet-Lotus Seeds", EFoodType::Vegetable, EEffectType::Hasty, 1.0f, 0.0f, 0.3f, 14.0f };

	//sneaky (stealth)
	FIngredient SneakySnail = { 39,"Sneaky River Snail", EFoodType::Meat, EEffectType::Sneaky, 2.0f, 0.0f, 1.3f, 5.0f };
	FIngredient StealthfinTrout = {40, "Stealthfin Trout", EFoodType::Meat, EEffectType::Sneaky, 2.0f, 0.0f, 1.3f, 10.0f };
	FIngredient SilentPrincess = { 41,"Silent Princess", EFoodType::Vegetable, EEffectType::Sneaky, 2.0f, 0.0f, 1.3f, 15.0f };

	//mighty (attack increase)
	FIngredient MightyBanana = { 42,"Mighty Bananas", EFoodType::Fruit, EEffectType::Mighty, 1.0f, 0.0f, 0.2f, 14.0f };
	FIngredient MightyCarp = { 43,"Mighty Carp", EFoodType::Meat, EEffectType::Mighty, 2.0f, 0.0f, 0.20f, 14.0f };
	FIngredient MightyPorgy = { 44,"Mighty Porgy", EFoodType::Meat, EEffectType::Mighty, 2.0f, 0.0f, 0.2f, 21.0f };
	FIngredient Razorshroom = { 45,"Razorshroom", EFoodType::Mushroom, EEffectType::Mighty, 1.0f, 0.0f, 0.20f, 14.0f };
	FIngredient MightyThistle = { 46,"Mighty Thistle", EFoodType::Vegetable, EEffectType::Mighty, 0.0f, 0.0f, 0.20f, 7.0f };

	//tough (defence increaase)
	FIngredient Ironshroom = { 47,"Ironshroom", EFoodType::Mushroom, EEffectType::Tough, 1.0f, 0.0f, 0.20f, 14.0f };
	FIngredient Pumpkin = { 48,"Fortified Pumpkin", EFoodType::Vegetable, EEffectType::Tough, 1.0f, 0.0f, 0.20f, 14.0f };
	FIngredient ArmoredCarp = { 49,"Armored Carp", EFoodType::Meat, EEffectType::Tough, 2.0f, 0.0f, 0.20f, 14.0f };
	FIngredient IronshellCrab = { 50,"Ironshell Crab", EFoodType::Meat, EEffectType::Tough, 1.0f, 0.0f, 0.20f, 14.0f };
	FIngredient Armoranth = { 51,"Armoranth", EFoodType::Vegetable, EEffectType::Tough, 0.0f, 0.0f, 0.20f, 7.0f };


	BaseIngredients.Add(Apple);
	BaseIngredients.Add(RawMeat);
	BaseIngredients.Add(RawGourmetMeat);
	BaseIngredients.Add(SankeCarp);
	BaseIngredients.Add(HyruleHerb);
	BaseIngredients.Add(PalmFruit);
	BaseIngredients.Add(Butter);
	BaseIngredients.Add(Wheat);
	BaseIngredients.Add(Milk);
	BaseIngredients.Add(Wildberry);
	BaseIngredients.Add(HylianShroom);
	BaseIngredients.Add(Salt);
	BaseIngredients.Add(Acorn);

	HeartyIngredients.Add(Truffle);
	HeartyIngredients.Add(HeartyBass);
	HeartyIngredients.Add(HeartyDurian);
	HeartyIngredients.Add(BigRadish);
	HeartyIngredients.Add(BlueshellSnail);

	EnergizingIngredients.Add(Stamella);
	EnergizingIngredients.Add(BrightCrab);
	EnergizingIngredients.Add(BeeHoney);
	EnergizingIngredients.Add(StaminokaBass);

	EnduringIngredients.Add(EnduraShroom);
	EnduringIngredients.Add(EnduraCarrot);

	ChillyIngredients.Add(Hydromelon);
	ChillyIngredients.Add(Chillshroom);
	ChillyIngredients.Add(ChillfinTrout);
	ChillyIngredients.Add(CoolSafflina);

	SpicyIngredients.Add(SpicyPepper);
	SpicyIngredients.Add(Sunshroom);
	SpicyIngredients.Add(SizzlefinTrout);

	ElectroIngredients.Add(Voltfruit);
	ElectroIngredients.Add(Zapshroom);
	ElectroIngredients.Add(VoltfinTrout);

	HastyIngredients.Add(Rushroom);
	HastyIngredients.Add(SwiftCarrot);
	HastyIngredients.Add(FleetLotus);

	SneakyIngredients.Add(SneakySnail);
	SneakyIngredients.Add(StealthfinTrout);
	SneakyIngredients.Add(SilentPrincess);

	MightyIngredients.Add(MightyBanana);
	MightyIngredients.Add(MightyCarp);
	MightyIngredients.Add(MightyPorgy);
	MightyIngredients.Add(Razorshroom);
	MightyIngredients.Add(MightyThistle);

	ToughIngredients.Add(Ironshroom);
	ToughIngredients.Add(Pumpkin);
	ToughIngredients.Add(ArmoredCarp);
	ToughIngredients.Add(IronshellCrab);
	ToughIngredients.Add(Armoranth);
	
	AllIngredients.Add(BaseIngredients);
	AllIngredients.Add(HeartyIngredients);
	AllIngredients.Add(EnergizingIngredients);
	AllIngredients.Add(EnduringIngredients);
	//AllIngredients.Add(FireproofIngredients);
	AllIngredients.Add(ChillyIngredients);
	AllIngredients.Add(SpicyIngredients);
	AllIngredients.Add(ElectroIngredients);
	AllIngredients.Add(HastyIngredients);
	AllIngredients.Add(SneakyIngredients);
	AllIngredients.Add(MightyIngredients);
	AllIngredients.Add(ToughIngredients);
}

