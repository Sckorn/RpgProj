// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgProj.h"
#include "HealthPotion.h"

UHealthPotion::UHealthPotion()
{
	
}

void UHealthPotion::Consume()
{
	ARpgProjCharacter * MainChar = Cast<ARpgProjCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (MainChar != nullptr)
	{
		MainChar->AddHealth(amountToAdd);
	}
}


