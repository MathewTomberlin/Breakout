// Fill out your copyright notice in the Description page of Project Settings.

#include "BallBase.h"


// Sets default values
ABallBase::ABallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABallBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

