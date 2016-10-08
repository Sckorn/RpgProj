// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgProj.h"
#include "CharacterInventory.h"


void UCharacterInventory::AddItemToInventory(int32 ItemID)
{
	if (ItemID > 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Called add tp inventory with ID %d"), ItemID);
		UInventoryItem * NewItem = UInventoryItem::CreateItem(ItemID);
		Items.Add(NewItem);
		UE_LOG(LogTemp, Error, TEXT("After add total amoint of items is %d"), Items.Num());
		ItemAdded = true;
	}
}

void UCharacterInventory::AddItemToInventory(UInventoryItem& SourceItem)
{
	
}

int32 UCharacterInventory::GetItemCount()
{
	return Items.Num();
}

UInventoryItem * UCharacterInventory::GetItemBlueprint(int32 Index)
{
	UE_LOG(LogTemp, Error, TEXT("Total items %d"), Items.Num());
	if (Index > -1 && Index < Items.Num())
	{
		//UInventoryItem * NewItem = UInventoryItem::CopyItem(Items[Index]);
		UE_LOG(LogTemp, Error, TEXT("Returned"));
		return Items[Index];
	}
	UE_LOG(LogTemp, Error, TEXT("Weird shit again?"));
	return nullptr;
}

UTexture2D * UCharacterInventory::GetItemIcon(int32 Index)
{
	UE_LOG(LogTemp, Error, TEXT("Total items %d"), Items.Num());
	if (Index > -1 && Index < Items.Num())
	{
		//UInventoryItem * NewItem = UInventoryItem::CopyItem(Items[Index]);
		UE_LOG(LogTemp, Error, TEXT("Returned"));
		return Items[Index]->GetItemIcon();
	}
	UE_LOG(LogTemp, Error, TEXT("Weird shit again?"));
	return nullptr;
}

FString UCharacterInventory::GetItemName(int32 Index)
{
	if (Index < 0 || Index > Items.Num())
	{
		FString str = L"";
		return str;
	}
	
	FString str = Items[Index]->GetItemName();
	return str;
}

bool UCharacterInventory::IsItemOfType(int32 index, EOverallItemTypes compType)
{
	if (index < 0 || index >= Items.Num())
	{
		return false;
	}

	return Items[index]->ItemOfType(compType);
}

