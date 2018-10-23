// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PaddleController.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API APaddleController : public APlayerController
{
	GENERATED_BODY()
public:
	APaddleController();

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	//Input functions
	void Move_XAxis(float AxisValue);
	//Input functions
	void ActionButton();
	
	//Input variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PaddlePhysics)
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PaddlePhysics)
	float speed;

	UFUNCTION(BlueprintCallable)
	void SpawnFunction();

	virtual void BeginPlay() override;

	TSubclassOf<class APaddle> PaddleBlueprint;
	TSubclassOf<class AMyActor> BallBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PaddlePhysics)
	AMyActor* Ball;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PaddlePhysics)
	APaddle* Paddle;

	UFUNCTION(BlueprintImplementableEvent)
	void Die();

	UFUNCTION(BlueprintImplementableEvent)
	void GetPoints(int points);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PaddlePhysics)
	bool BallInMotion;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PaddlePhysics)
	bool Paused;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PaddlePhysics)
	bool MainMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PaddlePhysics)
	FVector PaddleSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PaddlePhysics)
	FVector BallSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PaddlePhysics)
	float killZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PaddlePhysics)
	float Multiplier;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ResetLevel(bool overrideSpawn);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void LoadingScreen(bool show);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void HitPaddle();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void HitWall();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void HitPickup();
};
