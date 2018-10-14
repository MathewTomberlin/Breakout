// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Paddle.h"
#include "PaddleController.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(SceneComponent);

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetEnableGravity(true);
	MeshComponent->SetNotifyRigidBodyCollision(true);
	MeshComponent->SetLinearDamping(1.0f);
	MeshComponent->OnComponentHit.AddDynamic(this, &APickup::OnCompHit);
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MeshComponent->GetComponentLocation().Z < ((APaddleController*)GetWorld()->GetFirstPlayerController())->killZ) {
		Destroy();
	}
}

void APickup::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		if (OtherActor->IsA(APaddle::StaticClass())) {
			((APaddleController*)GetWorld()->GetFirstPlayerController())->Multiplier++;
			Destroy();
		}
	}
}

