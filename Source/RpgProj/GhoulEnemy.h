// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseEnemy.h"
#include "Runtime/Engine/Classes/Animation/AnimBlueprint.h"
#include "GhoulEnemy.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJ_API AGhoulEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:
	AGhoulEnemy();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void AttackPlayerWithAnim() override;

	/*virtual void AttackPlayer() override;*/
	
};
