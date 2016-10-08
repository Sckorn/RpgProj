// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgProj.h"
#include "RpgProjCharacter.h"
#include "RpgProjProjectile.h"
#include "CollisionQueryParams.h"
#include "BaseEnemy.h"


// Sets default values
ABaseEnemy::ABaseEnemy()
{
	PlayStarted = false;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	MainEnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainEnemyMesh"));
	MainEnemyMesh->AttachTo(DefaultSceneRoot);
	MainEnemyMesh->RelativeRotation = FRotator(0.0f, 270.0f, 0.0f);
	MainEnemyMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	//MainEnemyMesh->SetNotifyRigidBodyCollision(true);

	MainCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MainCollision"));
	MainCollision->AttachTo(DefaultSceneRoot);
	MainCollision->InitCapsuleSize(22.0f, 44.0f);
	MainCollision->RelativeLocation = FVector(0.0f, 0.0f, 70.0f);
	MainCollision->RelativeScale3D = FVector(2.0f, 2.0f, 2.0f);
	MainCollision->SetCollisionProfileName(FName("BlockAll"));
	MainCollision->SetNotifyRigidBodyCollision(true);
	
	//MainEnemyMesh->OnComponentHit.AddDynamic(this, &ABaseEnemy::OnHit);
	SetActorEnableCollision(true);
	OnActorHit.AddDynamic(this, &ABaseEnemy::OnHit);

	PlayerDetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerDetectionSphere"));
	PlayerDetectionSphere->AttachTo(DefaultSceneRoot);
	PlayerDetectionSphere->InitSphereRadius(32.0f);
	PlayerDetectionSphere->RelativeLocation = FVector(0.0f, 0.0f, 70.0f);
	PlayerDetectionSphere->RelativeScale3D = FVector(5.0f, 5.0f, 5.0f);
	PlayerDetectionSphere->bGenerateOverlapEvents = true;
	PlayerDetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PlayerDetectionSphere->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	PlayerDetectionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	initialZ = GetActorLocation().Z;

	bShowDebug = false;
	bPlayerSpotted = false;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	IsIdle = true;
	IsStanding = false;
	IsAttacking = false;
	IsWalking = false;
	IsDamaged = false;
	IsDead = false;

	SetStandingTimer();

	Health = MaxHealth;
	//PlayStarted = true;
	//GetWorldTimerManager().SetTimer(StandingStateTimer, this, &ABaseEnemy::SetStandingState, 5.0f);
}

// Called every frame
void ABaseEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (IsDead) return;

	TArray<AActor *> OverlappedActors;
	GetOverlappingActors(OverlappedActors, ARpgProjCharacter::StaticClass());

	//LineOfSight();
	if (bPlayerSpotted)
	{
		TrackPlayer(DeltaTime);
	}
	else
	if (OverlappedActors.Num() > 0)
	{
#ifdef DEBUG
		UE_LOG(LogTemp, Warning, TEXT("Total actors found %d"), OverlappedActors.Num());
#endif // DEBUG

		//if (LineOfSight())
		{
			//UE_LOG(LogTemp, Error, TEXT("Passed LineOfSight?"));
			if (GetWorldTimerManager().IsTimerActive(StandingStateTimer))
			{
				GetWorldTimerManager().PauseTimer(StandingStateTimer);
			}

			if (GetWorldTimerManager().IsTimerActive(IdleStateTimer))
			{
				GetWorldTimerManager().PauseTimer(IdleStateTimer);
			}

			ARpgProjCharacter * MainCharacter = Cast<ARpgProjCharacter>(OverlappedActors[0]);
			if (MainCharacter != nullptr)
			{
				float DistanceBetween = GetDistanceTo(MainCharacter);

#ifdef DEBUG
				UE_LOG(LogTemp, Warning, TEXT("Distance between %f and attack distance %f"), DistanceBetween, AttackDistance);
#endif // DEBUG


				if (!IsAttacking)
				{
					if (DistanceBetween <= AttackDistance)
					{
						if (bShowDebug)
						{
							UE_LOG(LogTemp, Error, TEXT("DAFUQ!?"));
						}
						IsAttacking = true;
						IsIdle = false;
					}
					else
					{
						IsAttacking = false;

						bPlayerSpotted = true;
					}
				}
				else
				{
					if (DistanceBetween > AttackDistance)
						IsAttacking = false;
				}
			}
			else
			{
#ifdef DEBUG
				UE_LOG(LogTemp, Warning, TEXT("Cast failed"));
#endif // DEBUG

			}
		}
	}
	else
	{
		IsAttacking = false;
		IsWalking = false;
	}
}

int32 ABaseEnemy::GetCurrentHealth() const
{
	return Health;
}

int32 ABaseEnemy::GetMaxHealth() const
{
	return MaxHealth;
}

void ABaseEnemy::SetHealth(int32 amount)
{
	Health = amount;
}

void ABaseEnemy::SetIdlingState()
{
	IsIdle = true;
	IsStanding = false;

	GetWorldTimerManager().SetTimer(StandingStateTimer, this, &ABaseEnemy::SetStandingState, 5.0f);
}

void ABaseEnemy::SetStandingState()
{
	IsIdle = false;
	IsStanding = true;

	GetWorldTimerManager().SetTimer(IdleStateTimer, this, &ABaseEnemy::SetIdlingState, 5.0f);
}

void ABaseEnemy::AttackPlayer()
{
#ifdef DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Player attack routine invoked!"));
#endif // DEBUG


	IsWalking = false;
	IsAttacking = true;

	ARpgProjCharacter * MainCharater = Cast<ARpgProjCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	float distance = GetDistanceTo(MainCharater);
	if (distance <= AttackDistance)
	{
#ifdef DEBUG
		UE_LOG(LogTemp, Warning, TEXT("In distance to attack let's call the function."));
#endif // DEBUG

		MainCharater->DamagePlayer(DamageDealt);
	}

	if(GetWorldTimerManager().IsTimerPaused(IdleStateTimer))
	{
		GetWorldTimerManager().UnPauseTimer(IdleStateTimer);
	}

	if (GetWorldTimerManager().IsTimerPaused(StandingStateTimer))
	{
		GetWorldTimerManager().IsTimerPaused(StandingStateTimer);
	}

	IsAttacking = false;
}

void ABaseEnemy::DamageActor(int32 DamageDealt)
{
	if (Health > 0)
	{
#ifdef DEBUG
		UE_LOG(LogTemp, Warning, TEXT("Actor %s health before decrease is %d HP"), *GetName(), Health);
#endif // DEBUG

		int32 resultHealth = Health - DamageDealt;

		if (resultHealth < 0)
		{
			Health = 0;
		}
		else
		{
			Health -= DamageDealt;
		}

#ifdef DEBUG
		UE_LOG(LogTemp, Warning, TEXT("Actor %s health after decrease is %d HP"), *GetName(), Health);
#endif // DEBUG

		if (Health > 0)
			IsDamaged = true;
		else
			ActorIsDeadRoutine();
	}
	else
	{
		ActorIsDeadRoutine();
	}
}

void ABaseEnemy::ActorIsDeadRoutine()
{
#ifdef DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Actor %s is dead starting death routine"), *GetName());
#endif // DEBUG
	IsDead = true;
	IsDamaged = false;
	IsAttacking = false;
	IsWalking = false;
	IsIdle = false;
	IsStanding = false;

}

void ABaseEnemy::AdvanceIdleTimer()
{
#ifdef DEBUG
	//UE_LOG(LogTemp, Warning, TEXT("Advancing standing timer current tick %d of %d"), ActiveStandingTimerLength, StandingStateDuration);
#endif // DEBUG

	if (ActiveStandingTimerLength > 0)
	{
		if (IsIdle) IsIdle = false;
		if (!IsStanding) IsStanding = true;

		--ActiveStandingTimerLength;
		if (!ActiveIdleTimerLength)
		{
			SetIdleTimer();
		}
	}
}

void ABaseEnemy::AdvanceStandingTimer()
{
#ifdef DEBUG
	//UE_LOG(LogTemp, Warning, TEXT("Advancing idle timer current tick %d of %d"), ActiveIdleTimerLength, IdleStateDuration);
#endif // DEBUG

	if (ActiveIdleTimerLength)
	{
		if (IsStanding) IsStanding = false;
		if (!IsIdle) IsIdle = true;

		--ActiveIdleTimerLength;
		if (!ActiveIdleTimerLength)
		{
			SetStandingTimer();
		}
	}
}

void ABaseEnemy::SetIdleTimer()
{
	ActiveIdleTimerLength = IdleStateDuration;
	GetWorldTimerManager().SetTimer(IdleStateTimer, this, &ABaseEnemy::AdvanceIdleTimer, 1.0f, true);
}

void ABaseEnemy::SetStandingTimer()
{
	ActiveStandingTimerLength = StandingStateDuration;
	GetWorldTimerManager().SetTimer(StandingStateTimer, this, &ABaseEnemy::AdvanceStandingTimer, 1.0f, true);
}

void ABaseEnemy::AttackPlayerWithAnim()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack with anim from base class!"));
}

USkeletalMeshComponent * ABaseEnemy::GetMainMeshComponent()
{
	return MainEnemyMesh;
}

void ABaseEnemy::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
#ifdef DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Enemy with name %s is hit by enemy of class %s"), *GetName(), *OtherActor->GetClass()->GetName());
#endif // DEBUG

	ARpgProjCharacter * MainCharRef = Cast<ARpgProjCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (MainCharRef != nullptr)
	{
#ifdef DEBUG
		UE_LOG(LogTemp, Warning, TEXT("Not null?"));
		UE_LOG(LogTemp, Warning, TEXT("Proj class is %s other actor class is %s"), *MainCharRef->ProjectileClass->StaticClass()->GetName(), *OtherActor->StaticClass()->GetName());
#endif

		ARpgProjCharacter * MainChar = Cast<ARpgProjCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (MainChar != nullptr)
		{
#ifdef DEBUG
			UE_LOG(LogTemp, Warning, TEXT("I am hit by character!"));
#endif

			if (!IsDamaged)
			{
				DamageActor(MainChar->InflictedDamage());
				IsDamaged = true;

#ifdef DEBUG
				UE_LOG(LogTemp, Error, TEXT("Health after damage is %d"), Health);
#endif
			}
		}

		/*ARpgProjProjectile * projectile = Cast<ARpgProjProjectile>(OtherActor);
		if (projectile != nullptr)
		{
#ifdef DEBUG
			UE_LOG(LogTemp, Warning, TEXT("I am hit by projectile!"));
#endif

			if (!IsDamaged)
			{
				DamageActor(projectile->DamageDealth);
				IsDamaged = true;
#ifdef DEBUG
				UE_LOG(LogTemp, Error, TEXT("Health after damage is %d"), Health);
#endif
			}
		}*/
	}
}

void ABaseEnemy::CheckIfDead()
{
	if (Health <= 0)
	{
		ActorIsDeadRoutine();
	}
}

void ABaseEnemy::OnActorIsDead()
{
	ARpgProjCharacter * MainChar = Cast<ARpgProjCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (MainChar != nullptr)
	{
		MainChar->MainCharacterClassReference->IncreaseKillCount();
	}

	this->Destroy();
}

bool ABaseEnemy::LineOfSight()
{
	ARpgProjCharacter * MainChar = Cast<ARpgProjCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (MainChar != nullptr)
	{
		if (bShowDebug)
		{
			UE_LOG(LogTemp, Error, TEXT("Got a character?"));
		}
		
		const FName TraceTag("MyTraceTag");

		GWorld->DebugDrawTraceTag = TraceTag;
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
		RV_TraceParams.bTraceComplex = true;
		RV_TraceParams.bTraceAsyncScene = true;
		RV_TraceParams.bReturnPhysicalMaterial = false;
		RV_TraceParams.AddIgnoredActor(this);
		RV_TraceParams.TraceTag = TraceTag;

		FHitResult HitResult(ForceInit);
		FVector dir = MainChar->GetActorLocation() - GetActorLocation();
		dir.Normalize();

		FVector target = FVector(GetActorLocation().X + 100.0f, GetActorLocation().Y, GetActorLocation().Z + 10.0f);
		FVector myPos = GetActorLocation();
		FVector myPosForTrace(myPos.X, myPos.Y, myPos.Z + 70.0f);
		bool isHit = GWorld->LineTraceSingleByChannel(HitResult, GetActorLocation(), (dir * 100.0f), ECollisionChannel::ECC_MAX, RV_TraceParams);

		if (isHit)
		{
			if (bShowDebug)
			{
				if (HitResult.bBlockingHit)
				{
					UE_LOG(LogTemp, Error, TEXT("Blocking hit"));
				}
				UE_LOG(LogTemp, Error, TEXT("Was hit?"));
				if (HitResult.GetActor() == nullptr)
				{
					UE_LOG(LogTemp, Error, TEXT("Some really weird shit is going on here"));
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Actor name is %s"), *HitResult.GetActor()->GetName());
				}
			
				if (HitResult.GetComponent() == nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("Component too"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Component name %s, its type %s"), *HitResult.GetComponent()->GetName(), *HitResult.GetComponent()->StaticClass()->GetName());
				}
			}

			//UE_LOG(LogTemp, Error, TEXT("Actor of class %s"), *HitResult.GetActor()->GetName());
			ARpgProjCharacter * IsChar = Cast<ARpgProjCharacter>(HitResult.GetActor());
			if (IsChar != nullptr)
			{
				if (bShowDebug)
				{
					UE_LOG(LogTemp, Error, TEXT("I hit a character!"));
				}
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
	{
		return false;
	}
}

void ABaseEnemy::TrackPlayer(float DeltaTime)
{
	if (bPlayerSpotted)
	{
		ARpgProjCharacter * MainChar = Cast<ARpgProjCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (MainChar != nullptr)
		{
			float DistanceBetween = GetDistanceTo(MainChar);
			if (DistanceBetween <= ActiveTrackingDistance)
			{
				if (DistanceBetween <= AttackDistance)
				{
					IsAttacking = true;
					IsWalking = false;
					IsIdle = false;
				}
				else
				{
					IsAttacking = false;

					FVector dir = MainChar->GetActorLocation() - GetActorLocation();
					dir.Normalize();
					FRotator rot = dir.Rotation();//FRotationMatrix::MakeFromX(dir).Rotator();
					FRotator rott = FRotator(0.0f, rot.Yaw, 0.0f);
					FVector initScale = GetActorScale3D();

					SetActorRotation(FMath::Lerp(GetActorRotation(), rott, DeltaTime * 2.5f));

					FRotator currentRot = GetActorRotation();

					float rotationDifference = FMath::Abs(currentRot.Yaw - rott.Yaw);

					UE_LOG(LogTemp, Error, TEXT("Rotation to face character is %s, rotation %s"), *rott.ToString(), *GetActorRotation().ToString());
					if (rotationDifference < 0.2f)
					{
						UE_LOG(LogTemp, Warning, TEXT("Facing the character, let's advance him!"));

						if (GetWorldTimerManager().IsTimerActive(StandingStateTimer))
						{
							GetWorldTimerManager().PauseTimer(StandingStateTimer);
						}

						if (GetWorldTimerManager().IsTimerActive(IdleStateTimer))
						{
							GetWorldTimerManager().PauseTimer(IdleStateTimer);
						}

						IsWalking = true;

						FVector source = FVector(GetActorLocation().X, GetActorLocation().Y, initialZ);
						FVector mcPos = MainChar->GetActorLocation();
						FVector destination = FVector(mcPos.X, mcPos.Y, initialZ);

						if (bShowDebug)
						{
							FVector res = FMath::Lerp(source, destination, DeltaTime);
							UE_LOG(LogTemp, Warning, TEXT("Enemy lerp offset %d; %d; %d"), res.X, res.Y, res.Z);
						}

						AddActorLocalOffset(FVector(10.0f, 0.0f, 0.0f));
					}
				}
			}
			else
			{
				bPlayerSpotted = false;
				IsAttacking = false;
				IsWalking = false;

				IsIdle = true;

				if (GetWorldTimerManager().IsTimerActive(StandingStateTimer))
				{
					GetWorldTimerManager().UnPauseTimer(StandingStateTimer);
				}

				if (GetWorldTimerManager().IsTimerActive(IdleStateTimer))
				{
					GetWorldTimerManager().UnPauseTimer(IdleStateTimer);
				}
			}
		}
	}
}