// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "WuBinaTownTest/WuBianCharacter.h"

APickup::APickup()
{
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	InteractableMesh->SetSimulatePhysics(true);

	ItemName = FString("Enter an item name here...");

	InteractableHelpText = FString("Press E to Pick item up");

	value = 0;

	Maxnum = 1;
}

void APickup::BeginPlay()
{
	InteractableHelpText = FString::Printf(TEXT("%s:Press E to pick up"), *ItemName);

}

void APickup::Interact_Implementation()
{
	AWuBianCharacter* Character = Cast<AWuBianCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Character->AddItemToInventory(this))
	{
		OnPickedUp();

	}
}

void APickup::Use_Implementation()
{
	GLog->Log("Use() from base pickup class : YOU SHOULD NOT BE SEEING THIS");
}


void APickup::OnPickedUp()
{
	InteractableMesh->SetVisibility(false);
	InteractableMesh->SetSimulatePhysics(false);
	InteractableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}
