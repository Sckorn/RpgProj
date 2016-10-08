// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "PlayerMainGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJ_API UPlayerMainGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main User Widget")
		FString PlayerMainGameWidgetName;
	
	
};
