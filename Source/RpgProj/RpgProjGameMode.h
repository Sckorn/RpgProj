// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "Blueprint/UserWidget.h"
#include "SoldierCharacterClass.h"
#include "BanditCharacterClass.h"
#include "MysticCharacterClass.h"
#include "InventoryItem.h"
#include "RpgProjGameMode.generated.h"

UCLASS(minimalapi)
class ARpgProjGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	bool bMainMenuLevel;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game HUD")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
		UUserWidget * CurrentWidget;

public:
	ARpgProjGameMode();

	UFUNCTION(BlueprintCallable, Category = "Game HUD")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "Game HUD")
		void SetMainMenuLevel(bool value);

	UFUNCTION(BlueprintCallable, Category = "Game HUD")
		bool GetMainMenuLevel();

	UFUNCTION(BlueprintCallable, Category = "Game HUD")
		uint8 GetCurrentCharacterClassI();

	UFUNCTION(BlueprintCallable, Category = "Player Data")
		void InitializePersistentInventory(class UCharacterInventory * Inv);


	UPROPERTY()
		AActor * CurrentActivePropWithItem;

	UPROPERTY()
		UClass * ActivePropClassRef;
};



