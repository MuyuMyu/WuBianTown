// Fill out your copyright notice in the Description page of Project Settings.


#include "WuBianCharacter.h"
#include "WuBinaTownTestGameModeBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AWuBianCharacter::AWuBianCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmCom = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmCom->bUsePawnControlRotation = true;
	SpringArmCom->SetupAttachment(RootComponent);

	CameraCom = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraCom->SetupAttachment(SpringArmCom);

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	Reach = 550.0f;

	HEalth = 100.0f;

	Magic = 100.0f;



}

void AWuBianCharacter::UpdateGold(int32 Amount)
{
	Gold += Amount;
}

float AWuBianCharacter::GetPlayerHealth()
{
	return HEalth;
}

float AWuBianCharacter::GetPlayerMagic()
{
	return Magic;
}

bool AWuBianCharacter::AddItemToInventory(APickup* Item)
{
	if (Item != NULL)
	{
		const int32 AvailableSlot = Inventory.Find(nullptr);
		if (AvailableSlot != INDEX_NONE)
		{
			Inventory[AvailableSlot] = Item;
			return true;

		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("你无法携带更多物品"));
			return false;
		}


	}
	else return false;

}

UTexture2D* AWuBianCharacter::GetThumbnailAtInventorySlot(int32 Slot)
{
	if (Inventory[Slot]!=NULL)
	{

		return Inventory[Slot]->PickupThumbnail;

	}
	else return nullptr;

}

FString AWuBianCharacter::GetItemNameAtInventorySlot(int32 Slot)
{
	if (Inventory[Slot] != NULL)
	{
		return Inventory[Slot]->ItemName;
	}
	else return FString("None");

}

void AWuBianCharacter::UseItemAtInventorySlot(int32 Slot)
{
	if (Inventory[Slot] != NULL)
	{
		Inventory[Slot]->Use_Implementation();
		Inventory[Slot] = NULL;

	}


}

// Called when the game starts or when spawned
void AWuBianCharacter::BeginPlay()
{
	Super::BeginPlay();

	Inventory.SetNum(4);

	CurrentInteractable = nullptr;
	
}

void AWuBianCharacter::MoveFoward(float value)
{
	FRotator ControlRot = GetControlRotation();

	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), value);
}

void AWuBianCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();

	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, value);

}

void AWuBianCharacter::StartAcceleration()
{
	float ChaSpeed = GetCharacterMovement()->MaxWalkSpeed;
	if (GetCharacterMovement()->MaxWalkSpeed != 4 * ChaSpeed)
		GetCharacterMovement()->MaxWalkSpeed *= AccelerationMultiplier;
}

void AWuBianCharacter::EndAcceleratioan()
{
	float ChaSpeed = GetCharacterMovement()->MaxWalkSpeed / 4;
	if (GetCharacterMovement()->MaxWalkSpeed != ChaSpeed)
		GetCharacterMovement()->MaxWalkSpeed /= AccelerationMultiplier;
}

void AWuBianCharacter::SlowWalk()
{
	if (CurrentCharacterState != CS_SlowWalk)
	{

	}
}

uint8 AWuBianCharacter::GetCharacterState()
{
	return CurrentCharacterState;
}

void AWuBianCharacter::SetCharacterState(uint8 NewState)
{
	CurrentCharacterState = NewState;
	
}

void AWuBianCharacter::ToggleInventory()
{
	AWuBinaTownTestGameModeBase* GameMod = Cast<AWuBinaTownTestGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMod->GetHUDState()==GameMod->HS_Ingame)
	{
		GameMod->ChangeHUDState(GameMod->HS_Inventory);
	}
	else
	{
		GameMod->ChangeHUDState(GameMod->HS_Ingame);
	}
}

void AWuBianCharacter::Interact()
{
	if (CurrentInteractable != nullptr)
	{
		CurrentInteractable->Interact_Implementation();
	}
}

void AWuBianCharacter::CheckForInteractables()
{
	//获取相机前方向量
	FRotator CameraRotation = GetControlRotation();
	FVector ForwardVector = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::X);

	//射线开始与结束位置
	FVector StartTrace = CameraCom->GetComponentLocation();
	FVector EndTrace = (ForwardVector * Reach) + StartTrace;
	
	//射线命中的结果
	FHitResult HitResult;

	//使射线忽略角色
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_WorldDynamic, CQP);

	AInteractable* PotentialInteractable = Cast<AInteractable>(HitResult.GetActor());

	if (PotentialInteractable == nullptr)
	{
		HelpText = FString("");
		CurrentInteractable = nullptr;
		//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 3);
		return;
	}
	else
	{
		CurrentInteractable = PotentialInteractable;
		HelpText = PotentialInteractable->InteractableHelpText;
		//DrawDebugLine(GetWorld(),StartTrace, EndTrace, FColor::Green, false, 3);
	}

}

// Called every frame
void AWuBianCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckForInteractables();




}

// Called to bind functionality to input
void AWuBianCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWuBianCharacter::MoveFoward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWuBianCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AWuBianCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Rise", this, &AWuBianCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AWuBianCharacter::Jump);

	PlayerInputComponent->BindAction("Acceleration", IE_Pressed, this, &AWuBianCharacter::StartAcceleration);
	PlayerInputComponent->BindAction("Acceleration", IE_Released, this, &AWuBianCharacter::EndAcceleratioan);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AWuBianCharacter::Interact);
	PlayerInputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AWuBianCharacter::ToggleInventory);


}

