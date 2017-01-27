// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealPlayground.h"
#include "SpookyCube.h"


// Sets default values
ASpookyCube::ASpookyCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeRoot = CreateDefaultSubobject <USceneComponent>(TEXT("CubeRoot"));
	RootComponent = CubeRoot;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMesh->AttachToComponent(CubeRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root

	CubeTrigger = CreateAbstractDefaultSubobject<UBoxComponent>(TEXT("CubeTrigger"));
	CubeTrigger->bGenerateOverlapEvents = true; // turn on overlap
	CubeTrigger->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	CubeTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASpookyCube::OnPlayerTriggerRust); // call function on overlap
	CubeTrigger->OnComponentEndOverlap.AddDynamic(this, &ASpookyCube::OnPlayerExitRust);
	CubeTrigger->AttachToComponent(CubeRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root

	RustAmount = 1.0f; // default of 1.0 is no rust, 0 would be all rust
}

// Called when the game starts or when spawned
void ASpookyCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpookyCube::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if(bRustEffectTriggered) // if we stand in trigger box start rusting
	{
		if (RustAmount > 0.0f)
		{
			RustAmount -= DeltaTime;
		}
	}
	if (!bRustEffectTriggered) // if we are outside of trigger box remove rusting
	{
		if (RustAmount < 1.0f)
		{
			RustAmount += DeltaTime;
		}
	}

	UMaterialInstanceDynamic* RustMaterialInstance = CubeMesh->CreateDynamicMaterialInstance(0); // getting the first material from the instance
	if (RustMaterialInstance != nullptr) // if it has succeedded in getting material
	{
		RustMaterialInstance->SetScalarParameterValue(FName("RustAmount"), RustAmount);
	}

}

void ASpookyCube::OnPlayerTriggerRust(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	bRustEffectTriggered = true;
}

void ASpookyCube::OnPlayerExitRust(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	bRustEffectTriggered = false;
}

