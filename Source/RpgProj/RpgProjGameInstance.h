// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "RpgProjCharacter.h"
#include "BaseCharacterClass.h"
#include "RpgProjGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJ_API URpgProjGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	URpgProjGameInstance(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Name")
		FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Class")
		ECharacterGameClasses ChosenCharacterClass;

	UFUNCTION(BlueprintCallable, Category = "Character Interactions")
		void PreserveCharacter();

	UPROPERTY()
	UBaseCharacterClass * MainCharacterClassReference;

	UPROPERTY()
	UCharacterInventory * MainCharacterCurrentInventory;
};
