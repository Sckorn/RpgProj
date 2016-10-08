// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "RpgProj.h"
#include "RpgProjHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

ARpgProjHUD::ARpgProjHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshiarTexObj.Object;
	bShowCrosshair = true;
}


void ARpgProjHUD::DrawHUD()
{
	Super::DrawHUD();
	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	if (bShowCrosshair)
	{
		Canvas->DrawItem(TileItem);
	}
}

void ARpgProjHUD::BeginPlay()
{
	Super::BeginPlay();

	FStringClassReference MyWidgetClassRef(TEXT("/Game/CustomContent/HUD/MainMenu.MainMenu_C"));//(TEXT("/Game/CustomContent/HUD/MainCharacterInterface.MainCharacterInterface_C"));
	if (UClass* MyWidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>())
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MyWidgetClass);
		//MainPlayerWidget = CreateWidget<UUserWidget>(GetWorld(), MyWidgetClass);
	}

	if (CurrentWidget != nullptr)
	{
		CurrentWidget->AddToViewport();
	}
}

void ARpgProjHUD::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void ARpgProjHUD::DrawMainMenuWidget()
{
	if (MainPlayerWidget != nullptr)
	{
		MainPlayerWidget->RemoveFromViewport();
		FStringClassReference MyWidgetClassRef(TEXT("/Game/CustomContent/HUD/MainMenu.MainMenu_C"));
		if (UClass* MyWidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>())
		{
			MainPlayerWidget = CreateWidget<UUserWidget>(GetWorld(), MyWidgetClass);
		}

		if (MainPlayerWidget != nullptr)
		{
			MainPlayerWidget->AddToViewport();
		}
	}
}

