// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpookyCube.generated.h"

UCLASS()
class UNREALPLAYGROUND_API ASpookyCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpookyCube();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//root component for cube
	UPROPERTY(EditAnywhere)
		USceneComponent* CubeRoot;
	
	//mesh for the cube
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* CubeMesh;

	//trigger for the cube
	UPROPERTY(EditAnywhere)
		UBoxComponent* CubeTrigger;
	
	//function call when a player enters collision box and triggers the rust effect
	UFUNCTION()
		void OnPlayerTriggerRust(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//function call when a player leaves collision box and untriggers the rust effect
	UFUNCTION()
		void OnPlayerExitRust(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	bool bRustEffectTriggered;

	float RustAmount;
};
