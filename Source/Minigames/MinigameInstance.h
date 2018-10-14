// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MinigameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API UMinigameInstance : public UGameInstance
{
	GENERATED_BODY()

	UMinigameInstance();
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int RemainingLives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int DifficultySetting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int TotalScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	bool MainMenu;
};
