// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "RpgProj.h"
#include "RpgProjGameMode.h"
#include "RpgProjHUD.h"
#include "RpgProjCharacter.h"
#include "RpgProjGameInstance.h"

void ARpgProjGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);

	ARpgProjCharacter * MainCharacter = Cast<ARpgProjCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	CurrentActivePropWithItem = nullptr;
	ActivePropClassRef = nullptr;

	bMainMenuLevel = false;

	URpgProjGameInstance * gi = Cast<URpgProjGameInstance>(GetGameInstance());

	if (gi != nullptr && MainCharacter != nullptr)
	{
		if (gi->MainCharacterClassReference == nullptr)
		{
			switch (gi->ChosenCharacterClass)
			{
			case ECharacterGameClasses::Bandit: 
			{
				UE_LOG(LogTemp, Error, TEXT("Creating character of type Bandit!"));
				gi->MainCharacterClassReference = ConstructObject<UBanditCharacterClass>(UBanditCharacterClass::StaticClass());//NewObject<UBanditCharacterClass>();
				gi->MainCharacterClassReference->SubclassReference = UBanditCharacterClass::StaticClass();
				MainCharacter->MainCharacterClassReference = gi->MainCharacterClassReference;
				MainCharacter->ClassRef = UBanditCharacterClass::StaticClass();
				MainCharacter->MainCharacterClassReference->SetName(gi->CharacterName);
			}
			break;
			case ECharacterGameClasses::Mystic:
			{
				UE_LOG(LogTemp, Error, TEXT("Creating character of type mystic!"));
				gi->MainCharacterClassReference = ConstructObject<UMysticCharacterClass>(UMysticCharacterClass::StaticClass());
				gi->MainCharacterClassReference->SubclassReference = UMysticCharacterClass::StaticClass();
				MainCharacter->MainCharacterClassReference = gi->MainCharacterClassReference;
				MainCharacter->ClassRef = UMysticCharacterClass::StaticClass();
				MainCharacter->MainCharacterClassReference->SetName(gi->CharacterName);
			}
			break;
			case ECharacterGameClasses::Soldier:
			{
				UE_LOG(LogTemp, Error, TEXT("Creating character of type soldier!"));
				gi->MainCharacterClassReference = ConstructObject<USoldierCharacterClass>(USoldierCharacterClass::StaticClass());//NewObject<USoldierCharacterClass>();
				gi->MainCharacterClassReference->SubclassReference = USoldierCharacterClass::StaticClass();
				MainCharacter->MainCharacterClassReference = gi->MainCharacterClassReference;
				MainCharacter->ClassRef = USoldierCharacterClass::StaticClass();
				MainCharacter->MainCharacterClassReference->SetName(gi->CharacterName);
			}
			break;
			default:
				break;
			}
		}
		else
		{
			MainCharacter->MainCharacterClassReference = gi->MainCharacterClassReference;
			MainCharacter->ClassRef = gi->MainCharacterClassReference->SubclassReference;
			//MainCharacter->MainCharacterClassReference->SetName(gi->CharacterName);
		}

		if (MainCharacter != nullptr && MainCharacter->MainCharacterClassReference != nullptr)
		{
			MainCharacter->SetHealth();
			MainCharacter->SetStamina();
			MainCharacter->CalculateAttackDamage();
		}
	}
}

ARpgProjGameMode::ARpgProjGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = ARpgProjHUD::StaticClass();
}

void ARpgProjGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Error, TEXT("Main level flag is %s"), (bMainMenuLevel ? TEXT("true") : TEXT("false")));
	if (bMainMenuLevel)
	{
		ARpgProjHUD * hud = Cast<ARpgProjHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
		hud->bShowCrosshair = false;
		ARpgProjCharacter * MainChar = Cast<ARpgProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (MainChar != nullptr)
		{
			//MainChar->GetMesh()->SetVisibility(false);
			ARpgProjHUD * hud = Cast<ARpgProjHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
			
			hud->bShowCrosshair = false;
			//hud->DrawMainMenuWidget();
		}
	}
}

void ARpgProjGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void ARpgProjGameMode::SetMainMenuLevel(bool value)
{
	bMainMenuLevel = value;

	if (bMainMenuLevel)
	{
		ACharacter * MainCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (MainCharacter != nullptr)
		{
			//MainCharacter
		}
	}
}

bool ARpgProjGameMode::GetMainMenuLevel()
{
	return bMainMenuLevel;
}

uint8 ARpgProjGameMode::GetCurrentCharacterClassI()
{
	URpgProjGameInstance * gi = Cast<URpgProjGameInstance>(GetGameInstance());
	if (gi != nullptr)
	{
		return (uint8)gi->ChosenCharacterClass;
	}
	else
	{
		return 200;
	}
}

void ARpgProjGameMode::InitializePersistentInventory(class UCharacterInventory * Inv)
{
	if (Inv != nullptr)
	{
		URpgProjGameInstance * gm = Cast<URpgProjGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (gm != nullptr)
		{
			gm->MainCharacterCurrentInventory = Inv;
		}
	}
}