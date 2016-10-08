// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgProj.h"
#include "SoldierCharacterClass.h"

USoldierCharacterClass::USoldierCharacterClass() : Super()
{
	//KillCount = 0;
	//UE_LOG(LogTemp, Error, TEXT("Soldier default constructor kill count is %d"), KillCount);
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterStats(TEXT("DataTable'/Game/AdditionalContent/CharacterFiles/Characters.Characters'"));
	if (CharacterStats.Succeeded())
	{
		CharacterStatsData = CharacterStats.Object;
		if (CharacterStatsData != nullptr)
		{
			static const FString ContextString(TEXT("GENERAL"));
			FCharacterClassStatsData * Stats = CharacterStatsData->FindRow<FCharacterClassStatsData>(*FString::Printf(TEXT("%d"), 1), ContextString);
			if (Stats != nullptr)
			{
				Strength = Stats->Strength;
				Agility = Stats->Agility;
				RecalculateBaseDamage();

				Vitality = Stats->Vitality;
				RecalculateMaxHealth();

				Sturdiness = Stats->Sturdiness;
				RecalculateMaxStamina();

				Intellect = Stats->Intellect;
				Awareness = Stats->Awareness;
				Luck = Stats->Luck;
			}
		}
	}
}

void USoldierCharacterClass::PerformSpecialAction()
{
	UE_LOG(LogTemp, Error, TEXT("Soldier class special action!"));
}

