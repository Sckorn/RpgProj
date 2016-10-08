// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgProj.h"
#include "BaseProp.h"


// Sets default values
ABaseProp::ABaseProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isConsumed = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));

	RootComponent = DefaultSceneRoot;

	FAttachmentTransformRules * rules = new FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	PropMainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PropMainMesh"));
	PropMainMesh->RelativeLocation = FVector(0.0f, 0.0f, 0.0f);
	PropMainMesh->AttachToComponent(RootComponent, *rules);
	//PropMainMesh->AttachTo(RootComponent);

	PlayerNearSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerDetectionSphere"));
	PlayerNearSphere->RelativeLocation = FVector(0.0f, 0.0f, 0.0f);
	PlayerNearSphere->SetSphereRadius(100.0f);
	PlayerNearSphere->AttachToComponent(RootComponent, *rules);
	//PlayerNearSphere->AttachTo(RootComponent);

	PropParticleEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MainPropEmitter"));
	PropParticleEmitter->RelativeLocation = FVector(0.0f, 0.0f, 0.0f);
	PropParticleEmitter->AttachToComponent(RootComponent, *rules);
}

// Called when the game starts or when spawned
void ABaseProp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProp::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TArray<AActor *> OvpActors;
	GetOverlappingActors(OvpActors, ARpgProjCharacter::StaticClass());
	ARpgProjCharacter * MainChar = Cast<ARpgProjCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (OvpActors.Num() > 0)
	{
		if (HasItems)
		{
			ARpgProjCharacter * MainChar = Cast<ARpgProjCharacter>(OvpActors[0]); //should be only one
			if (!MainChar->GetCanPickup())
				MainChar->SetCanPickup(true);

			if (MainChar->bPickedUp)
			{
				//for (auto item : ItemsIDs)
				for (int32 i = 0; i < ItemsIDs.Num(); i++)
				{
					MainChar->GetInventory()->AddItemToInventory(ItemsIDs[i]);
				}

				MainChar->bPickedUp = false;
				MainChar->SetCanPickup(false);
				HasItems = false;
				isConsumed = true;
				Destroy();
			}
		}
		else
		{
			MainChar->SetCanPickup(false);
		}
	}
	else
	{
		MainChar->SetCanPickup(false);
	}
}

bool ABaseProp::IsConsumed()
{
	return isConsumed;
}

