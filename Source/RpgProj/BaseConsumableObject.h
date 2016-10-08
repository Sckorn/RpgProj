// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "RpgProjCharacter.h"
#include "BaseConsumableObject.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class RPGPROJ_API UBaseConsumableObject : public UObject
{
	GENERATED_BODY()
	
public:

	int32 ItemID;
	int32 IndexInInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Usage")
		USoundBase * UsageSound;

	UBaseConsumableObject();

	void Init(int32 _itemid, int32 _invind);

	virtual void Consume();
	
	
};
