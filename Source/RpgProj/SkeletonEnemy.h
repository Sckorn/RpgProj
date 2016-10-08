// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseEnemy.h"
#include "SkeletonEnemy.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJ_API ASkeletonEnemy : public ABaseEnemy
{
	GENERATED_BODY()

	ASkeletonEnemy();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
	
	
};
