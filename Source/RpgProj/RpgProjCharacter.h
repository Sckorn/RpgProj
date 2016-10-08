// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "RpgProjGameMode.h"
#include "CharacterInventory.h"
#include "BaseEnemy.h"
#include "BaseCharacterClass.h"
#include "RpgProjCharacter.generated.h"

class UInputComponent;

UENUM(BlueprintType)
enum class ECharacterGameClasses : uint8
{
	None,
	Soldier,
	Mystic,
	Bandit
};

UCLASS(config=Game)
class ARpgProjCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, Category = CharacterStats)
		int32 DefaultStaminaDecay;

	UPROPERTY(VisibleAnywhere, Category = CharacterStats)
		int32 StaminaRestoreRate;

	UPROPERTY(VisibleAnywhere)
		FTimerHandle StaminaRestoreTimer;

	bool bCanPickUp;

	bool bGamePaused;
public:
	ARpgProjCharacter();

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ARpgProjProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
		int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
		int32 MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
		int32 Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
		int32 MaxStamina;

	UFUNCTION(BlueprintCallable, Category = PlayerInteractions)
		void DamagePlayer(int32 damageDealt);

	UFUNCTION(BlueprintCallable, Category = PlayerInteractions)
		void DamagePlayerWithDistanceCheck(int32 DamageDealth, ABaseEnemy * AttackingEnemy);

	UFUNCTION(BlueprintCallable, Category = PlayerInteractions)
		void SetCanPickup(bool NewValue);

	UFUNCTION(BlueprintCallable, Category = PlayerInteractions)
		bool GetCanPickup();

	UFUNCTION(BlueprintCallable, Category = PlayerInteractions)
		void SetGamePaused(bool _isPaused);

	UFUNCTION(BlueprintCallable, Category = PlayerInteractions)
		bool GetGamePaused();

	UFUNCTION(BlueprintCallable, Category = PlayerInventory)
		UCharacterInventory * GetInventory();

	UFUNCTION(BlueprintCallable, Category = PlayerInteractions)
		int32 GetKillCount();

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		void SetHealth();

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		void SetStamina();

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		void CalculateAttackDamage();

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		int32 InflictedDamage();

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
		void AddHealth(int32 amount);

	/*UFUNCTION(BlueprintCallable, Category = InventoryOperations)
		virtual void AddItemToInventory(InventoryItem * ItemToAdd);*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
		bool IsDamaged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
		bool ActionPerformed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
		int32 PreviousHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
		int32 PreviousStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerInteractions)
		bool bPickedUp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterStats)
	UBaseCharacterClass * MainCharacterClassReference;

	UPROPERTY()
	UClass * ClassRef;

protected:
	
	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;

	void IncreaseStaminaPerTimer();

	void PickUpItem();

	void PauseGame();

	UPROPERTY()
	class UCharacterInventory * Inventory;

	UPROPERTY()
		int32 AttackDamage;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

