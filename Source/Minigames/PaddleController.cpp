// Fill out your copyright notice in the Description page of Project Settings.

#include "PaddleController.h"
#include "Paddle.h"
#include "MyActor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Slate.h"


APaddleController::APaddleController() {
	static ConstructorHelpers::FObjectFinder<UBlueprint>ItemBlueprint(TEXT("Blueprint'/Game/GameplayObjects/PaddleBP.PaddleBP'"));
	if (ItemBlueprint.Object) {
		PaddleBlueprint = (UClass*)ItemBlueprint.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint>Blueprint(TEXT("Blueprint'/Game/GameplayObjects/BallBP.BallBP'"));
	if (Blueprint.Object) {
		BallBlueprint = (UClass*)Blueprint.Object->GeneratedClass;
	}

	speed = 1000.0f;
	BallInMotion = false;
}

void APaddleController::BeginPlay() {
	FInputModeGameAndUI inputMode;
	inputMode.SetHideCursorDuringCapture(false);
	SetInputMode(inputMode);
	Multiplier = 1;
}

// Called to bind functionality to input
void APaddleController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	InputComponent->BindAxis("MoveX", this, &APaddleController::Move_XAxis);
	InputComponent->BindAction("ActionButton",IE_Pressed, this, &APaddleController::ActionButton);
}

void APaddleController::Move_XAxis(float AxisValue)
{
	// Move at 100 units per second forward or backward
	CurrentVelocity.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f) * speed;
}

void APaddleController::ActionButton()
{
	if (!BallInMotion && !MainMenu) {
		Ball->BeginMovement();
		BallInMotion = true;
	}
}

void APaddleController::SpawnFunction() // This never gets reached
{

	FActorSpawnParameters sp;
	sp.Name = "PlayerPaddle";
	sp.bNoFail = true;
	FVector location = PaddleSpawnLocation;
	FRotator rotation = FRotator(0.0f, 0.0f, 0.0f);

	UWorld *world = GetWorld();

	Paddle = world->SpawnActor<APaddle>(PaddleBlueprint, location, rotation, sp);

	sp.Name = "Ball";
	sp.bNoFail = true;
	location = BallSpawnLocation;
	rotation = FRotator(0.0f, 0.0f, 0.0f);

	Ball = world->SpawnActor<AMyActor>(BallBlueprint, location, rotation, sp);

	SetupInputComponent();
}


