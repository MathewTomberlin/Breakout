// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MinigamesGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API AMinigamesGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		AMinigamesGameModeBase();

		TSubclassOf<class APaddle> PaddleBlueprint;

public:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		bool CalculateLevelBricks;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int TotalBricks;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int RemainingBricks;
};
