// Fill out your copyright notice in the Description page of Project Settings.

#include "TestFPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"
#include "Engine/Scene.h"
#include "Engine/GameEngine.h"
#include "DrawDebugHelpers.h"
#include "ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "InteractableIngredient.h"
#include "InteractableCookedProduct.h"
#include "CookingPot.h"


// Sets default values
ATestFPSCharacter::ATestFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(RootComponent);
	CameraComp->SetRelativeLocation(FVector(20.0f, 0.0f, 50.0f));

	MovementComp = this->GetCharacterMovement();
	MovementComp->MaxWalkSpeed = 10.0f;
	MovementComp->AirControl = 1.0f;

	PlayerCollisionComp = this->GetCapsuleComponent();
	PlayerCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATestFPSCharacter::OnOverlapBegin);
	PlayerCollisionComp->OnComponentEndOverlap.AddDynamic(this, &ATestFPSCharacter::OnOverlapEnd);

	UStaticMesh *PlayerMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/Meshes/Chalice.Chalice'")));
	PlayerMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMeshComp->SetStaticMesh(PlayerMesh);
	PlayerMeshComp->SetupAttachment(CameraComp);
	PlayerMeshComp->SetRelativeLocationAndRotation(FVector(-20.0f, 0.0f, -50.0f), FQuat(0.0f, 0.0f, 0.0f, 0.0f));


	InteractablePositionComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IntPoint"));
	InteractablePositionComp->SetupAttachment(PlayerMeshComp);
	InteractablePositionComp->SetRelativeLocation(FVector(100.0f, -40.0f, 28.0f));
}

// Called when the game starts or when spawned
void ATestFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestFPSCharacter::PlayerForwardMovement(float Value)
{
	if (Value != 0.0f)
	{
		FVector MoveDirection = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(MoveDirection, Value);
	}
}

void ATestFPSCharacter::PlayerSideMovement(float Value)
{
	if (Value != 0.0f)
	{
		FVector MoveDirection = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(MoveDirection, Value);
	}
}

// Object Pickup code is taken from 10 Second Dungeon source
void ATestFPSCharacter::PlayerPickUpItem()
{
	if (!PlayerIsHoldingItem)
	{
		AActor *Obj = CanPlayerPickUpInteractableObj();
		if (Obj != NULL)
		{
			if (Obj->ActorHasTag("Ingredient"))
			{
				AInteractableIngredient* IngObj = Cast<AInteractableIngredient>(Obj);
				//Obj->InteractWithObject(InteractablePositionComp);
				IngObj->SetActorLocation(InteractablePositionComp->GetComponentLocation());
				IngObj->AttachToComponent(InteractablePositionComp, FAttachmentTransformRules::KeepWorldTransform);
				IngObj->DisableCollision();
				PlayerIsHoldingItem = true;
			}
			else if (Obj->ActorHasTag("Product"))
			{
				AInteractableCookedProduct* ProdObj = Cast<AInteractableCookedProduct>(Obj);
				//Obj->InteractWithObject(InteractablePositionComp);
				ProdObj->SetActorLocation(InteractablePositionComp->GetComponentLocation());
				ProdObj->AttachToComponent(InteractablePositionComp, FAttachmentTransformRules::KeepWorldTransform);
				PlayerIsHoldingItem = true;
			}

		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("hit return is null"));
		}
	}
}

void ATestFPSCharacter::PlayerThrowItem()
{
	if (PlayerIsHoldingItem) 
	{
		// check that it is not destroyed whilst holding
		AActor* ChildObj = InteractablePositionComp->GetChildComponent(0)->GetOwner();
		if (ChildObj) 
		{

			if (ChildObj != NULL && ChildObj->ActorHasTag("Ingredient"))
			{
				auto* HitObject = Cast<AInteractableIngredient>(ChildObj);
				FDetachmentTransformRules Rules{ EDetachmentRule::KeepWorld,EDetachmentRule::KeepWorld,EDetachmentRule::KeepWorld,false };
				HitObject->DetachFromActor(Rules);
				PlayerIsHoldingItem = false;
				HitObject->EnableCollision();
				HitObject->SetMoveSpeed(100.0f, CameraComp->GetComponentRotation().Vector());
				UE_LOG(LogTemp, Warning, TEXT("throwing item"));
			}
			else if (ChildObj != NULL && ChildObj->ActorHasTag("Product"))
			{
				auto* HitObject = Cast<AInteractableCookedProduct>(ChildObj);
				FDetachmentTransformRules Rules{ EDetachmentRule::KeepWorld,EDetachmentRule::KeepWorld,EDetachmentRule::KeepWorld,false };
				HitObject->DetachFromActor(Rules);
				PlayerIsHoldingItem = false;
				HitObject->SetMoveSpeed(100.0f, CameraComp->GetComponentRotation().Vector());
				UE_LOG(LogTemp, Warning, TEXT("throwing item"));
			}
		}
	}
}

void ATestFPSCharacter::PlayerCookItem()
{
	if (PlayerInCookingTrigger)
	{
		if (NearestCookingPot != NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("COOKING."));
			FCookedProduct Result = NearestCookingPot->GenerateCookedProduct();

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, Result.Name);			
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Health: %f"), Result.HealthRestore));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Stamina: %f"), Result.StaminaRestore));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Duration: %f"), Result.Duration));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Potency: %f"), Result.Potency));
		}
	}
}

// Called every frame
void ATestFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("PlayerForwardMovement", this, &ATestFPSCharacter::PlayerForwardMovement);
	PlayerInputComponent->BindAxis("PlayerSideMovement", this, &ATestFPSCharacter::PlayerSideMovement);
	PlayerInputComponent->BindAxis("PlayerHorizontalMouseMovement", this, &ATestFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerVerticalMouseMovement", this, &ATestFPSCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PlayerPickUpItem", EInputEvent::IE_Pressed, this, &ATestFPSCharacter::PlayerPickUpItem);
	PlayerInputComponent->BindAction("PlayerThrowItem", EInputEvent::IE_Pressed, this, &ATestFPSCharacter::PlayerThrowItem);
	PlayerInputComponent->BindAction("CookItems", EInputEvent::IE_Pressed, this, &ATestFPSCharacter::PlayerCookItem);

}

void ATestFPSCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

void ATestFPSCharacter::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	NearestCookingPot = NULL;
}

void ATestFPSCharacter::SetNearestValidCookingPot(ACookingPot* Pot)
{
	NearestCookingPot = Pot;
}


// basically 90% of this code is ripped from 10 second dungeon 
AActor *ATestFPSCharacter::CanPlayerPickUpInteractableObj()
{
	//trace a line from the players view to see if they are in range of an interactable object
	// offset the start vector so it doesn't detect the players own character.
	FHitResult OutHit = FHitResult(ForceInit);
	FVector CameraVec = CameraComp->GetComponentLocation();
	FVector StartVec = CameraVec + (CameraComp->GetComponentRotation().Vector() * 40.0f);
	FVector EndVec = CameraVec + (CameraComp->GetComponentRotation().Vector() * 1000.0f);
	FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, NULL);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = true;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartVec, EndVec, ECC_GameTraceChannel3, TraceParams))
	{
		DrawDebugLine(GetWorld(), StartVec, EndVec, FColor::Green, false, 5.f, ECC_WorldStatic, 1.f);

		if (OutHit.Actor->ActorHasTag("Ingredient"))
		{
			UE_LOG(LogTemp, Warning, TEXT("HIT Ingredient"));
			AInteractableIngredient* Obj = Cast<AInteractableIngredient>(OutHit.Actor.Get());		
			return Obj;
		}
		else if (OutHit.Actor->ActorHasTag("Product"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Product"));
			AInteractableCookedProduct* Obj = Cast<AInteractableCookedProduct>(OutHit.Actor.Get());
			return Obj;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		//DrawDebugLine(GetWorld(), StartVec, EndVec, FColor::Purple, false, 5.f, ECC_WorldStatic, 1.f);
		return nullptr;
	}
}

