// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "InventoryItem.h"
#include "CharacterInventory.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class RPGPROJ_API UCharacterInventory : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TArray<UInventoryItem *> Items;

public:

	void AddItemToInventory(int32 ItemID);
	void AddItemToInventory(UInventoryItem& SourceItem);

	UFUNCTION(BlueprintCallable, Category = ItemInteractions)
	UInventoryItem * GetItemBlueprint(int32 Index);

	UFUNCTION(BlueprintCallable, Category = ItemInteractions)
		UTexture2D * GetItemIcon(int32 Index);

	UFUNCTION(BlueprintCallable, Category = ItemInteractions)
		FString GetItemName(int32 Index);

	UFUNCTION(BlueprintCallable, Category = ItemInteractions)
		int32 GetItemCount();

	UFUNCTION(BlueprintCallable, Category = ItemInteractions)
		bool IsItemOfType(int32 index, EOverallItemTypes compType);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ItemInteractions)
		bool ItemAdded;

	FORCEINLINE	UInventoryItem * operator[] (int32 indexToReturn)
	{
		int32 arrayLength = Items.Num();
		if (Items.Num() > 0)
		{
			if (indexToReturn > -1 && indexToReturn < Items.Num())
			{
				return Items[indexToReturn];
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			return nullptr;
		}
	}
	
	
};
