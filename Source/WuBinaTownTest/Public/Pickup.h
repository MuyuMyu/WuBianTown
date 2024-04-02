// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class WUBINATOWNTEST_API APickup : public AInteractable
{
	GENERATED_BODY()
public:

	APickup();

	virtual void BeginPlay() override;

	virtual void Interact_Implementation() override;

	UFUNCTION(BlueprintNativeEvent)
	void Use();
	virtual void Use_Implementation();

	UPROPERTY(EditAnywhere, category = "Pickup Properties")
	UTexture2D* PickupThumbnail;//Àı¬‘Õº

	UPROPERTY(EditAnywhere, category = "Pickup Properties")
	FString ItemName;

	UPROPERTY(EditAnywhere, category = "Pickup Properties")
	FString ItemDescroption;

	UPROPERTY(EditAnywhere, category = "Pickup Properties")
	int32 Maxnum;

	UPROPERTY(EditAnywhere, category = "Pickup Properties")
	int32 value;

	void OnPickedUp();
	
};
