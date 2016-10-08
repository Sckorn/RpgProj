// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgProj.h"
#include "InventoryItem.h"

UInventoryItem::UInventoryItem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemDataObject(TEXT("DataTable'/Game/AdditionalContent/ItemsFiles/Items_0_9.Items_0_9'"));
	if (ItemDataObject.Succeeded())
	{
		ItemLoadData = ItemDataObject.Object;
	}
}

UInventoryItem * UInventoryItem::CreateItem(int32 ItemID)
{
	UInventoryItem * NewItem = ConstructObject<UInventoryItem>(UInventoryItem::StaticClass());//NewObject<UInventoryItem>();
	NewItem->SetItemID(ItemID);
	return NewItem;
}

UInventoryItem * UInventoryItem::CopyItem(UInventoryItem SourceItem)
{
	UE_LOG(LogTemp, Error, TEXT("Trying to copy item with id %d"), SourceItem.uniqeID);
	return nullptr;
}

void UInventoryItem::SetItemID(int32 _id)
{
	if (_id > 0)
	{
		this->ParseItemById(_id);
	}
}

void UInventoryItem::ParseItemById(int32 _id)
{
	if (_id > 0)
	{
		if (ItemLoadData != nullptr)
		{
			static const FString ContextString(TEXT("GENERAL"));
			FInventoryItemDataStructure * ItemData = ItemLoadData->FindRow<FInventoryItemDataStructure>(*FString::Printf(TEXT("%d"), _id), ContextString);

			if (ItemData != nullptr)
			{
				if (ItemData->ItemID != _id) UE_LOG(LogTemp, Error, TEXT("Wrong row name!"));
				UE_LOG(LogTemp, Error, TEXT("Got item with id %d and overall type %d"), ItemData->ItemID, ItemData->OverallItemType);
				uniqeID = ItemData->ItemID;
				hasModel = (ItemData->HasModel > 0) ? true : false;
				ObjectModelReferenceString = ItemData->ObjectModelReference;
				InventoryIconReferenceString = ItemData->InventoryIconReference;
				EOverallItemTypes itype = (EOverallItemTypes)ItemData->OverallItemType;
				//UE_LOG(LogTemp, Error, TEXT("Overall item type is %d"), (uint8));
				ItemGeneralType = itype;
				if (itype == EOverallItemTypes::Equipable) bCanBeEquipped = true;
				else
				{
					bCanBeEquipped = false;
				}

				if (ItemData->EquipableItemType > -1 && bCanBeEquipped)
				{
					uint8 itemTypeUI = (uint8)ItemData->EquipableItemType;
					EEquipableItemTypes etype = (EEquipableItemTypes)itemTypeUI;
					ItemEquipableType = etype;
				}

				ItemName = ItemData->ItemName;

				//InvokerClass = LoadC
			}
		}
	}
}

UTexture2D * UInventoryItem::GetItemIcon()
{
	if (!InventoryIconReferenceString.IsEmpty())
	{
		UTexture2D * icon = LoadObject<UTexture2D>(NULL, *InventoryIconReferenceString, NULL, 0, nullptr);
		return icon;
	}
	else
	{
		return nullptr;
	}
}

FString UInventoryItem::GetItemName()
{
	return ItemName;
}

bool UInventoryItem::ItemOfType(EOverallItemTypes typeToCompare)
{
	UE_LOG(LogTemp, Error, TEXT("Item ovr type is %d type to compare is %d"), (uint8)ItemGeneralType, (uint8)typeToCompare);
	if (ItemGeneralType == typeToCompare)
	{
		return true;
	}
	
	return false;
}


