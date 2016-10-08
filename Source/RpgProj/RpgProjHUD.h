// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "RpgProjHUD.generated.h"

UCLASS()
class ARpgProjHUD : public AHUD
{
	GENERATED_BODY()

public:
	ARpgProjHUD();

	virtual void BeginPlay() override;
	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	class UUserWidget* MainPlayerWidget;

	UFUNCTION(BlueprintCallable, Category = "Game HUD")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "Game HUD")
		void DrawMainMenuWidget();

	UPROPERTY()
		bool bShowCrosshair;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game HUD")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
		UUserWidget * CurrentWidget;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
	
};

