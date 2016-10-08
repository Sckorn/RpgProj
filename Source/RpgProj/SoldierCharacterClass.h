// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCharacterClass.h"
#include "SoldierCharacterClass.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJ_API USoldierCharacterClass : public UBaseCharacterClass
{
	GENERATED_BODY()
	
public:

	USoldierCharacterClass();

	virtual void PerformSpecialAction() override;
	
	
};
