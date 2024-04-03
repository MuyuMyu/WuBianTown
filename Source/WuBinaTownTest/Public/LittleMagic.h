// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicBaseClass.h"
#include "LittleMagic.generated.h"

/**
 * 
 */
UCLASS()
class WUBINATOWNTEST_API ALittleMagic : public AMagicBaseClass
{
	GENERATED_BODY()

public:
	ALittleMagic();

	virtual void Interact_Implementation() override;
	
	/*
	void DistoryMagic();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	FVector FirstLocation;
	FVector CurrentLocation;
	FVector CFValue;
	*/
};
