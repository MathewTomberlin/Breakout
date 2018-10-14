// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"

UCLASS()
class MINIGAMES_API ABrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComponent;

	TSubclassOf<class APickup> PickupBlueprint;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DestroyedBrick();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DamagedBrick();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrickHealth)
	float maxhealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BrickHealth)
	float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrickHealth)
	bool bonusBlock;
	
};
