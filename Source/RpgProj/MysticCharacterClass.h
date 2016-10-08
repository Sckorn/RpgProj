// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCharacterClass.h"
#include "MysticCharacterClass.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJ_API UMysticCharacterClass : public UBaseCharacterClass
{
	GENERATED_BODY()

public:
	UMysticCharacterClass();

	virtual void PerformSpecialAction() override;
	
	
};
