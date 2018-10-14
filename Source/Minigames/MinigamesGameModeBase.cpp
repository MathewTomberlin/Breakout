// Fill out your copyright notice in the Description page of Project Settings.

#include "MinigamesGameModeBase.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "PaddleController.h"
#include "Paddle.h"
#include "UObject/ConstructorHelpers.h"

AMinigamesGameModeBase::AMinigamesGameModeBase()
{
	PlayerControllerClass = APaddleController::StaticClass(); // This gets called
	DefaultPawnClass = APaddle::StaticClass();
}


