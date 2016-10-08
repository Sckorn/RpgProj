// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgProj.h"
#include "GhoulEnemy.h"

AGhoulEnemy::AGhoulEnemy() : Super()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainEnemyMeshFinder(TEXT("SkeletalMesh'/Game/CustomContent/Actors/Enemies/MEshes/ghoul.ghoul'"));
	if (MainEnemyMeshFinder.Succeeded())
	{
		MainEnemyMesh->SkeletalMesh = MainEnemyMeshFinder.Object;
	}
	MainEnemyMesh->RelativeScale3D = FVector(0.75f, 0.75f, 0.75f);

	FString AnimClassStringTest = "Class'/Game/CustomContent/Actors/Enemies/Animations/Ghoulenemy.Ghoulenemy_C'";

	// load the class
	UClass* AnimationClass = LoadObject<UClass>(NULL, *AnimClassStringTest);
	if (!AnimationClass) UE_LOG(LogTemp, Error, TEXT("Class not found!"));

	// assign the anim blueprint class to your skeletal mesh component
	MainEnemyMesh->SetAnimInstanceClass(AnimationClass);

	MainCollision->RelativeLocation = FVector(0.0f, 0.0f, 85.0f);
	MainCollision->RelativeScale3D = FVector(2.0f, 2.0f, 2.0f);
	MainCollision->InitCapsuleSize(22.0f, 55.0f);

	PlayerDetectionSphere->RelativeLocation = FVector(0.0f, 0.0f, 120.0f);
	PlayerDetectionSphere->RelativeScale3D = FVector(5.0f, 5.0f, 5.0f);
	PlayerDetectionSphere->SetSphereRadius(40.0f);

	AttackDistance = 140.0f;
	MaxHealth = 200;
	SetHealth(200);
	DamageDealt = 20;

	ActiveTrackingDistance = AttackDistance * 2;

	MovementSpeed = 12.5f;
}

void AGhoulEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsWalking)
	{

	}
}

void AGhoulEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGhoulEnemy::AttackPlayerWithAnim()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack with anim from GhoulEnemy"));
	
}

/*void AGhoulEnemy::AttackPlayer()
{
	UE_LOG(LogTemp, Error, TEXT("Attack player from GhoulEnemy"));
}*/


