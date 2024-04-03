// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicBaseClass.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;



UCLASS()
class WUBINATOWNTEST_API AMagicBaseClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicBaseClass();


	UFUNCTION(BlueprintNativeEvent)
	void Interact();
	virtual void Interact_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere);
	USphereComponent* SphereComp;//�������

	UPROPERTY(VisibleAnywhere);
	UProjectileMovementComponent* MovementComp;//Ͷ�����˶����������һ��ֱ�ߵ��ٶ�

	UPROPERTY(VisibleAnywhere);
	UParticleSystemComponent* EffectComp;//����ϵͳ���


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
