// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicBaseClass.h"

// Sets default values
AMagicBaseClass::AMagicBaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMagicBaseClass::Interact_Implementation()
{
	GLog->Log("Interact basic class: Interact() YOU SHOULD NOT BE SEEING THIS");
}

// Called when the game starts or when spawned
void AMagicBaseClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagicBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

