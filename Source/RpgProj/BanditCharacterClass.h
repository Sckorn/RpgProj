// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCharacterClass.h"
#include "BanditCharacterClass.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJ_API UBanditCharacterClass : public UBaseCharacterClass
{
	GENERATED_BODY()

public:

	UBanditCharacterClass();

	virtual void PerformSpecialAction() override;
	
	
};
