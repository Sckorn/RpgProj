// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "InventoryItem.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable)
struct FInventoryItemDataStructure : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadOnly, Category = "GO")
		int32 ItemID;

	UPROPERTY(BlueprintReadOnly, Category = "GO")
		int32 HasModel;

	UPROPERTY(BlueprintReadOnly, Category = "GO")
		FString ObjectModelReference;

	UPROPERTY(BlueprintReadOnly, Category = "GO")
		FString InventoryIconReference;

	UPROPERTY(BlueprintReadOnly, Category = "GO")
		uint8 OverallItemType;

	UPROPERTY(BlueprintReadOnly, Category = "GO")
		int32 EquipableItemType;

	UPROPERTY(BlueprintReadOnly, Category = "GO")
		FString ItemName;

	UPROPERTY(BlueprintReadOnly, Category = "GO")
		FString ClassName;

};

UENUM(BlueprintType)
enum class EOverallItemTypes : uint8
{
	UnknownItemType,
	Consumable,
	Usable,
	Equipable

};

UENUM(BlueprintType)
enum class EEquipableItemTypes : uint8
{
	UnknownItemType,
	Armor,
	Weapon,
	Trinket
};

UCLASS()
class RPGPROJ_API UInventoryItem : public UObject
{
	GENERATED_BODY()

private:
	TCHAR * PathToItemFiles = L"Content/AdditionalContent/ItemsFiles/";
	
protected:
	int32 uniqeID;
	bool hasModel;
	FString ObjectModelReferenceString;
	FString InventoryIconReferenceString;
	FString ItemName;

	bool bCanBeEquipped;
	EOverallItemTypes ItemGeneralType;
	EEquipableItemTypes ItemEquipableType;

	UDataTable * ItemLoadData;

	UClass * InvokerClass;

public:
	UInventoryItem();

	void SetItemID(int32 _id);

	void ParseItemById(int32 _id);

	UFUNCTION(BlueprintCallable, Category = ItemData)
		UTexture2D * GetItemIcon();

	UFUNCTION(BlueprintCallable, Category = ItemData)
		FString GetItemName();

	UFUNCTION(BlueprintCallable, Category = ItemData)
		bool ItemOfType(EOverallItemTypes typeToCompare);

	static UInventoryItem * CreateItem(int32 ItemID);
	static UInventoryItem * CopyItem(UInventoryItem SourceItem);	
};
