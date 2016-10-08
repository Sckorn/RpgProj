// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgProj.h"
#include "SkeletonEnemy.h"

ASkeletonEnemy::ASkeletonEnemy() : Super()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainEnemyMeshFinder(TEXT("SkeletalMesh'/Game/CustomContent/Actors/Enemies/MEshes/Skeleton_Skin.Skeleton_Skin'"));
	if (MainEnemyMeshFinder.Succeeded())
	{
		MainEnemyMesh->SkeletalMesh = MainEnemyMeshFinder.Object;
	}
	MainEnemyMesh->RelativeScale3D = FVector(10.0f, 10.0f, 10.0f);

	FString AnimClassStringTest = "Class'/Game/CustomContent/Actors/Enemies/Animations/SkeletonEnemy.SkeletonEnemy_C'";

	// load the class
	UClass* AnimationClass = LoadObject<UClass>(NULL, *AnimClassStringTest);
	if (!AnimationClass) UE_LOG(LogTemp, Error, TEXT("Class not found! SkeletonEnemy"));

	// assign the anim blueprint class to your skeletal mesh component
	MainEnemyMesh->SetAnimInstanceClass(AnimationClass);

	MainCollision->RelativeLocation = FVector(0.0f, 0.0f, 70.0f);
	MainCollision->RelativeScale3D = FVector(2.0f, 2.0f, 2.0f);
	MainCollision->InitCapsuleSize(22.0f, 44.0f);

	PlayerDetectionSphere->RelativeLocation = FVector(0.0f, 0.0f, 70.0f);
	PlayerDetectionSphere->RelativeScale3D = FVector(5.0f, 5.0f, 5.0f);
	PlayerDetectionSphere->SetSphereRadius(32.0f);

	AttackDistance = 150.0f;
	MaxHealth = 100;
	SetHealth(100);
	DamageDealt = 5;

	ActiveTrackingDistance = AttackDistance * 2;

	MovementSpeed = 10.0f;
}

void ASkeletonEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkeletonEnemy::BeginPlay()
{
	Super::BeginPlay();
}


