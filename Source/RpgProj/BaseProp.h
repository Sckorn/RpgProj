// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RpgProjCharacter.h"
#include "RpgProjGameMode.h"
#include "BaseProp.generated.h"

UCLASS()
class RPGPROJ_API ABaseProp : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent * DefaultSceneRoot;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent * PropMainMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = PlayerDetection)
	class USphereComponent * PlayerNearSphere;

	UPROPERTY(VisibleDefaultsOnly, Category = PlayerDetection)
	class UParticleSystemComponent * PropParticleEmitter;

private:
	bool isConsumed;
	
public:	
	// Sets default values for this actor's properties
	ABaseProp();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropItems)
		bool HasItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PropItems)
		TArray<int32> ItemsIDs;

	UFUNCTION(BlueprintCallable, Category = PropState)
		bool IsConsumed();
	
};
