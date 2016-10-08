// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgProj.h"
#include "RpgProjGameInstance.h"

URpgProjGameInstance::URpgProjGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void URpgProjGameInstance::PreserveCharacter()
{
	ARpgProjCharacter * MainChar = Cast<ARpgProjCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (MainChar != nullptr)
	{
		URpgProjGameInstance * gi = Cast<URpgProjGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (gi != nullptr)
		{
			UBaseCharacterClass * newObj = NewObject<UBaseCharacterClass>();
			bool bInitialObjectDuplicated = false;
			switch (gi->ChosenCharacterClass)
			{
				case ECharacterGameClasses::Bandit: 
				{
					newObj = DuplicateObject<UBanditCharacterClass>((UBanditCharacterClass*)MainChar->MainCharacterClassReference, this);//ConstructObject<UBanditCharacterClass>(UBanditCharacterClass::StaticClass());
					bInitialObjectDuplicated = true;
				}
				break;
				case ECharacterGameClasses::Mystic: 
				{
					newObj = DuplicateObject<UMysticCharacterClass>((UMysticCharacterClass*)MainChar->MainCharacterClassReference, this);//ConstructObject<UMysticCharacterClass>(UMysticCharacterClass::StaticClass());
					bInitialObjectDuplicated = true;
				}
				break;
				case ECharacterGameClasses::Soldier: 
				{
					newObj = DuplicateObject<USoldierCharacterClass>((USoldierCharacterClass*)MainChar->MainCharacterClassReference, this);//ConstructObject<USoldierCharacterClass>(USoldierCharacterClass::StaticClass());
					bInitialObjectDuplicated = true;
				}
				break;
				default:
					break;
			}
			if (bInitialObjectDuplicated)
			{
				UE_LOG(LogTemp, Error, TEXT("New object constructed successfully!"));
				gi->MainCharacterClassReference = newObj;
			}
		}
	}
}


