// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WuBinaTownTestGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WUBINATOWNTEST_API AWuBinaTownTestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	AWuBinaTownTestGameModeBase();

	enum EHUDState :UINT8 
	{
		HS_Ingame,
		HS_Inventory,
		HS_Shop_General,
		HS_Shop_Weapon
		
	};

	void ApplyHUDChanges();

	uint8 GetHUDState();

	UFUNCTION(BlueprintCallable, Category = "HUD Function")
	void ChangeHUDState(uint8 NewState);

	bool ApplyHUD(TSubclassOf<class UUserWidget>WidgetToApply, bool bShowMOuseCursor, bool EnableClickEvent);

protected:

	uint8 HUDState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUDWidgets", Meta = (BlueprintProtected = true))
	TSubclassOf<class UUserWidget> IngameHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUDWidgets", Meta = (BlueprintProtected = true))
	TSubclassOf<class UUserWidget> InventoryHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUDWidgets", Meta = (BlueprintProtected = true))
	TSubclassOf<class UUserWidget> ShopGeneralHUDClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;


	
};
