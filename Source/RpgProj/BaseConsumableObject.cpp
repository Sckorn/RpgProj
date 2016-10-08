// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgProj.h"
#include "BaseConsumableObject.h"

UBaseConsumableObject::UBaseConsumableObject()
{
	
}

void UBaseConsumableObject::Consume()
{
	
}

void UBaseConsumableObject::Init(int32 _itemid, int32 _invind)
{
	ItemID = _itemid;
	IndexInInventory = _invind;
}

