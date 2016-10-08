// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseConsumableObject.h"
#include "RpgProjCharacter.h"
#include "HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJ_API UHealthPotion : public UBaseConsumableObject
{
	GENERATED_BODY()

public:
	int32 amountToAdd;

	UHealthPotion();
	
	void Consume() override;
};
