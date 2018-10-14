// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerLivesWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMES_API UPlayerLivesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data") 
	FString PlayerLives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int Points;

	UPlayerLivesWidget(const FObjectInitializer& ObjectInitializer);
};
