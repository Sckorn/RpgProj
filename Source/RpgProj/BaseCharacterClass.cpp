// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgProj.h"
#include "BaseCharacterClass.h"

UBaseCharacterClass::UBaseCharacterClass()
{
	KillCount = 0;
}

void UBaseCharacterClass::PerformSpecialAction()
{
	UE_LOG(LogTemp, Error, TEXT("Base class special action!"));
}

FString UBaseCharacterClass::GetCharacterName() const
{
	FString ret = CharacterName;
	return ret;
}

void UBaseCharacterClass::SetName(FString name)
{
	CharacterName = name;
}

void UBaseCharacterClass::IncreaseKillCount()
{
	++KillCount;
}

int32 UBaseCharacterClass::GetKillCount()
{
	return KillCount;
}

void UBaseCharacterClass::RecalculateBaseDamage()
{
	BaseDamage = (Strength + Agility) * __BASE_DAMAGE_RATIO__;
}

void UBaseCharacterClass::RecalculateMaxHealth()
{
	MaxHealth = Vitality * __HEALTH_RATIO__;
	CurrentHealth = MaxHealth;
}

void UBaseCharacterClass::RecalculateMaxStamina()
{
	MaxStamina = Sturdiness * __STAMINA_RATIO__;
	CurrentStamina = MaxStamina;
}

int32 UBaseCharacterClass::GetMaxHealth()
{
	return MaxHealth;
}

int32 UBaseCharacterClass::GetMaxStamina()
{
	return MaxStamina;
}

int32 UBaseCharacterClass::GetBaseDamage()
{
	return BaseDamage;
}

FCharacterClassStatsData UBaseCharacterClass::GetCharacterStatsStruct()
{
	FCharacterClassStatsData charData;
	charData.Agility = Agility;
	charData.Awareness = Awareness;
	charData.Intellect = Intellect;
	charData.Luck = Luck;
	charData.Strength = Strength;
	charData.Sturdiness = Sturdiness;
	charData.Vitality = Vitality;
	return charData;
}


