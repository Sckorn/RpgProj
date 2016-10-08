// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define DEBUG

#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

UCLASS(Abstract)
class RPGPROJ_API ABaseEnemy : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent * DefaultSceneRoot;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* MainEnemyMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	class UCapsuleComponent * MainCollision;

	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	class USphereComponent * PlayerDetectionSphere;

	UPROPERTY(VisibleDefaultsOnly, Category = PlayerInteraction)
	class TSubclassOf<AActor> MainCharacterClassRef;
private:
	FTimerHandle IdleStateTimer;
	FTimerHandle StandingStateTimer;
	FTimerHandle AttackDelayTimer;

	int32 Health;

	int32 ActiveIdleTimerLength;
	int32 ActiveStandingTimerLength;

	float initialZ;

	bool IsInLineOfSight;

	void AdvanceIdleTimer();
	void AdvanceStandingTimer();
	void SetIdleTimer();
	void SetStandingTimer();

	void TrackPlayer(float DeltaTime);
	
public:	
	// Sets default values for this actor's properties
	ABaseEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		int32 GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		int32 GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = AnimationControls)
		void SetIdlingState();

	UFUNCTION(BlueprintCallable, Category = AnimationControls)
		void SetStandingState();

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		void SetHealth(int32 amount);

	UFUNCTION(BlueprintCallable, Category = PlayerTracking)
		virtual void AttackPlayer();

	UFUNCTION(BlueprintCallable, Category = PlayerTracking)
		virtual void AttackPlayerWithAnim();

	UFUNCTION(BlueprintCallable, Category = PlayerTracking)
		virtual void DamageActor(int32 DamageDealth);

	UFUNCTION(BlueprintCallable, Category = AnimationControls)
		USkeletalMeshComponent * GetMainMeshComponent();

	UFUNCTION(BlueprintCallable, Category = AnimationControls)
		virtual void CheckIfDead();

	UFUNCTION(BlueprintCallable, Category = AnimationControls)
		virtual void OnActorIsDead();

	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, Category = PlayerTracking)
		virtual void ActorIsDeadRoutine();

	UFUNCTION(BlueprintCallable, Category = PlayerTracking)
		virtual bool LineOfSight();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimationControls)
		bool IsIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimationControls)
		bool IsStanding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimationControls)
		bool IsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimationControls)
		bool IsWalking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimationControls)
		bool IsDamaged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimationControls)
		bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerTracking)
		float AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerTracking)
		float ActiveTrackingDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerTracking)
		bool bPlayerSpotted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerTracking)
		int32 DamageDealt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerTracking)
		int32 IdleStateDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerTracking)
		int32 StandingStateDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
		int32 MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterBackground)
		bool PlayStarted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyDebug)
		bool bShowDebug;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerTracking)
		float MovementSpeed;
};
