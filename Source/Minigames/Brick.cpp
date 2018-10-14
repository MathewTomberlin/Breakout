// Fill out your copyright notice in the Description page of Project Settings.

#include "Brick.h"
#include "Kismet/GameplayStatics.h"
#include "PaddleController.h"
#include "MinigameInstance.h"
#include "Pickup.h"
#include "MinigamesGameModeBase.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint>ComboPickupBlueprint(TEXT("Blueprint'/Game/GameplayObjects/PickupBP.PickupBP'"));
	if (ComboPickupBlueprint.Object) {
		PickupBlueprint = (UClass*)ComboPickupBlueprint.Object->GeneratedClass;
	}

	//Set up the scene and mesh components
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SceneComponent->SetupAttachment(RootComponent);
	MeshComponent->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->SetNotifyRigidBodyCollision(true);
	MeshComponent->OnComponentHit.AddDynamic(this, &ABrick::OnCompHit);

	health = maxhealth;
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrick::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		health -= 1;
		DamagedBrick();

		if (health <= 0) {
			DestroyedBrick();

			if (bonusBlock) {
				FActorSpawnParameters sp;
				sp.Name = "ComboPickup";
				sp.bNoFail = true;
				FVector location = GetTargetLocation();
				FRotator rotation = FRotator(0.0f, 0.0f, 0.0f);

				UWorld *world = GetWorld();

				APickup* Pickup = world->SpawnActor<APickup>(PickupBlueprint, location, rotation, sp);
			}

			int difficulty = ((UMinigameInstance*)GetGameInstance())->DifficultySetting;
			((APaddleController*)(GetWorld()->GetFirstPlayerController()))->GetPoints(maxhealth * 100 * difficulty*((APaddleController*)(GetWorld()->GetFirstPlayerController()))->Multiplier);
		}
	}
}

