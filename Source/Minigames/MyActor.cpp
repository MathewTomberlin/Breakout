// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Paddle.h"
#include "Brick.h"
#include "MinigameInstance.h"
#include "PaddleController.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(SceneComponent);
}

void AMyActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	MeshComponent->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetEnableGravity(false);
	MeshComponent->SetNotifyRigidBodyCollision(true);
	MeshComponent->OnComponentHit.AddDynamic(this, &AMyActor::OnCompHit);
}

void AMyActor::BeginMovement() {
	switch (((UMinigameInstance*)GetWorld()->GetGameInstance())->DifficultySetting) {
	case 1:
		speed = 500.0f+ (((UMinigameInstance*)GetWorld()->GetGameInstance())->CurrentLevel*10);
		break;
	case 2:
		speed = 800.0f + (((UMinigameInstance*)GetWorld()->GetGameInstance())->CurrentLevel * 10);
		break;
	case 3:
		speed = 1200.0f + (((UMinigameInstance*)GetWorld()->GetGameInstance())->CurrentLevel * 10);
		break;
	}

	velocity = FVector(0, speed, -2 * speed);

	MeshComponent->AddImpulse(velocity, NAME_None, true);
}

// Called every frame
void AMyActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	MeshComponent->SetLockedAxis(EDOFMode::YZPlane);

	if(((APaddleController*)GetWorld()->GetFirstPlayerController())->BallInMotion)
		MeshComponent->SetPhysicsLinearVelocity(velocity.GetSafeNormal()*speed);

	//Ball died, reset it
	if (MeshComponent->GetComponentLocation().Z < ((APaddleController*)GetWorld()->GetFirstPlayerController())->killZ) {
		MeshComponent->SetWorldLocation(((APaddleController*)GetWorld()->GetFirstPlayerController())->BallSpawnLocation);
		MeshComponent->SetPhysicsLinearVelocity(velocity.GetSafeNormal()*0);
		((APaddleController*)GetWorld()->GetFirstPlayerController())->Multiplier = 1;

		((APaddleController*)GetWorld()->GetFirstPlayerController())->BallInMotion = false;
		((APaddleController*)GetWorld()->GetFirstPlayerController())->Die();
	}
}

void AMyActor::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		
		//FString velString = velocity.ToString();
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Velocity: %s"), *velString));
		FVector bounceDir = (Hit.ImpactPoint- OtherActor->GetActorLocation()).GetSafeNormal();
		FVector impactDir = (OtherActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();

		//Dot product of impact normal with up and right dir
		float upDir = FMath::Abs(FVector::DotProduct(NormalImpulse, FVector(0, 0, 1)));
		float rightDir = FMath::Abs(FVector::DotProduct(NormalImpulse, FVector(0, 1, 0)));

		if (OtherActor->IsA(APaddle::StaticClass())) {
			bounceDir = FVector(0, (HitComp->GetComponentLocation().Y-OtherComp->GetComponentLocation().Y)*0.01f, (HitComp->GetComponentLocation().Z - OtherComp->GetComponentLocation().Z > 0)?-FMath::Sign(HitComp->GetComponentLocation().Z - OtherComp->GetComponentLocation().Z):0);
			velocity = bounceDir.GetSafeNormal()*speed;
			((APaddleController*)GetWorld()->GetFirstPlayerController())->HitPaddle();
		} else if(!OtherActor->IsA(ABrick::StaticClass())) {
			((APaddleController*)GetWorld()->GetFirstPlayerController())->HitWall();
		}

		if (bounceDir.Z!=0) {
			//Invert velocity in the proper axis
			if (rightDir < upDir) {
				velocity = FVector(velocity.X, velocity.Y, velocity.Z*-1);
			}
			else if (rightDir > upDir) {
				velocity = FVector(velocity.X, velocity.Y*-1, velocity.Z);
			}
			else {
				velocity = -velocity;// FVector(velocity.X, velocity.Y*-1, velocity.Z*-1);
			}
		} else {
			velocity.Z = speed*5;
			velocity.Y *= 10;
		}

		//Add impulse to our ball
		//MeshComponent->AddImpulse(velocity,NAME_None,true);
	}
}