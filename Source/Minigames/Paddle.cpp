// Fill out your copyright notice in the Description page of Project Settings.

#include "Paddle.h"
#include "PaddleController.h"
#include "Camera/CameraComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "PlayerLivesWidget.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
APaddle::APaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	// Create a camera and a visible object
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetRelativeLocation(CameraRelativeLocation);
	CameraComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	MeshComponent->SetupAttachment(SceneComponent);
	
	speed = 100.0f;
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetEnableGravity(false);

}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MeshComponent->SetPhysicsLinearVelocity(((APaddleController*)GetWorld()->GetFirstPlayerController())->CurrentVelocity);
	MeshComponent->SetWorldRotation(FRotator(0.0f,0.0f,0.0f));
	MeshComponent->SetLockedAxis(EDOFMode::XYPlane);
}

