// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Public/Interactable.h"
#include "Public/Pickup.h"
#include "WuBianCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class WUBINATOWNTEST_API AWuBianCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWuBianCharacter();

	enum ECharacterState :UINT8
	{
		CS_AttackModel,
		CS_NormalModel
	};

	enum EChaMoveState :UINT8
	{
		CMS_NormalWalk,
		CMS_SlowWalk,
		CMS_Run
	};






	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	FString HelpText;

	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	int32 Gold;

	//���»�������
	UFUNCTION(BlueprintCallable, Category = "Inventory Function")
	void UpdateGold(int32 Amount);

	UFUNCTION(BlueprintPure, Category = "Character Function")
	float GetPlayerHealth();


	UFUNCTION(BlueprintPure, Category = "Character Function")
	float GetPlayerMagic();



	UFUNCTION(BlueprintPure, Category = "Inventory Function")
	bool AddItemToInventory(APickup* Item);

	//��ȡ��Ʒ����ͼ���������
	UFUNCTION(BlueprintPure, Category = "Inventory Function")
	UTexture2D* GetThumbnailAtInventorySlot(int32 Slot);

	//��ȡ��Ʒ����
	UFUNCTION(BlueprintPure, Category = "Inventory Function")
	FString GetItemNameAtInventorySlot(int32 Slot);

	//ʹ����Ʒ
	UFUNCTION(BlueprintCallable, Category = "Inventory Function")
	void UseItemAtInventorySlot(int32 Slot);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraCom;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmCom;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float AccelerationMultiplier = 2.0f;  // ����Ĭ�ϵļ��ٱ���Ϊ 2.0



	void PrimaryAttack();

	void MoveFoward(float value);

	void MoveRight(float value);

	void StartAcceleration();

	void EndAcceleratioan();

	void SlowWalk();

	uint8 GetCharacterState();

	void SetCharacterState(uint8 NewState);

	float HEalth;

	float Magic;

	UPROPERTY()
	uint8 CurrentCharacterState;

private:

	float Reach;

	//�л�����
	void ToggleInventory();

	void Interact();

	//���߼��ǰ���Ƿ�������
	void CheckForInteractables();

	UPROPERTY(EditAnywhere)
	TArray<APickup*>Inventory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	

	AInteractable* CurrentInteractable;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
