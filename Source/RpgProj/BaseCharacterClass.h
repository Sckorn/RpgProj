// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "BaseCharacterClass.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable)
struct FCharacterClassStatsData : public FTableRowBase
{	
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Character Stats")
		int32 Strength;

	UPROPERTY(BlueprintReadOnly, Category = "Character Stats")
		int32 Agility;

	UPROPERTY(BlueprintReadOnly, Category = "Character Stats")
		int32 Vitality;

	UPROPERTY(BlueprintReadOnly, Category = "Character Stats")
		int32 Sturdiness;

	UPROPERTY(BlueprintReadOnly, Category = "Character Stats")
		int32 Intellect;

	UPROPERTY(BlueprintReadOnly, Category = "Character Stats")
		int32 Awareness;

	UPROPERTY(BlueprintReadOnly, Category = "Character Stats")
		int32 Luck;

};

UCLASS(Abstract)
class RPGPROJ_API UBaseCharacterClass : public UObject
{
	GENERATED_BODY()
	
protected:
	int32 KillCount;

	UPROPERTY()
		int32 MaxHealth;
	int32 CurrentHealth;

	UPROPERTY()
		int32 MaxStamina;
	int32 CurrentStamina;

	int32 DamageDealt;
	int32 BaseDamage;

#pragma region CharacterStats

	int32 Strength; //damage for bare hands and strength based weapons
	int32 Agility; //damage for agility based weapons, speed of different actions
	int32 Vitality; //amount of HP and resists rates
	int32 Sturdiness; //amount of stamins and resist rates
	int32 Intellect;
	int32 Awareness;
	int32 Luck;

#pragma endregion

	int32 IntoxicationLevel;
	int32 IllnessLevel;
	int32 MadnessLevel;

	UDataTable * CharacterStatsData;

public:

	FString CharacterName;

	UBaseCharacterClass();
	
	UPROPERTY()
	UClass * SubclassReference;

	UFUNCTION(BlueprintCallable, Category = CharacterSpecialAction)
		virtual void PerformSpecialAction();

	UFUNCTION(BlueprintCallable, Category = CharcterInfo)
		FString GetCharacterName() const;

	UFUNCTION(BlueprintCallable, Category = CharcterInfo)
		void SetName(FString CharName);

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		void RecalculateBaseDamage();

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		void RecalculateMaxHealth();

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		void RecalculateMaxStamina();

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		int32 GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		int32 GetMaxStamina();

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		int32 GetBaseDamage();

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		FCharacterClassStatsData GetCharacterStatsStruct();

	UFUNCTION(BlueprintCallable, Category = CharacterInteraction)
		void IncreaseKillCount();

	UFUNCTION(BlueprintCallable, Category = CharacterInteraction)
		int32 GetKillCount();
	
};
