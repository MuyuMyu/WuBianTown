// Copyright Epic Games, Inc. All Rights Reserved.


#include "WuBinaTownTestGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "WuBianCharacter.h"


void AWuBinaTownTestGameModeBase::BeginPlay()
{
	ApplyHUDChanges();

}

AWuBinaTownTestGameModeBase::AWuBinaTownTestGameModeBase()
{
}

void AWuBinaTownTestGameModeBase::ApplyHUDChanges()
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromParent();
	}
	
	switch (HUDState)
	{
	case EHUDState::HS_Ingame: {
		ApplyHUD(IngameHUDClass, false, false);
		break;
	}
	case EHUDState::HS_Inventory: {
		ApplyHUD(InventoryHUDClass, true, true);
		break;
	}
	case EHUDState::HS_Shop_General: {
		ApplyHUD(ShopGeneralHUDClass, false, false);
		break;
	}
	default: {
		ApplyHUD(IngameHUDClass, false, false);
		break;
	}
	}

}

uint8 AWuBinaTownTestGameModeBase::GetHUDState()
{
	return HUDState;
}

void AWuBinaTownTestGameModeBase::ChangeHUDState(uint8 NewState)
{
	HUDState = NewState;
	ApplyHUDChanges();
}

bool AWuBinaTownTestGameModeBase::ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool bShowMOuseCursor, bool EnableClickEvent)
{
	AWuBianCharacter* MyCharacter = Cast<AWuBianCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	if (WidgetToApply != nullptr)
	{
		//ʹ���ɼ�
		MyController->bShowMouseCursor = bShowMOuseCursor;
		MyController->bEnableClickEvents = EnableClickEvent;

		//��������
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetToApply);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
			return true;
		}
		else return false;

	}
	else return false;
}
