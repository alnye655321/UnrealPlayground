// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealPlayground.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot")); // initialize a component
	RootComponent = PickupRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	PickupMesh->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root component of PickupRoot, "->" dereferences a pointer to select a field

	PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
	PickupBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector
	PickupBox->bGenerateOverlapEvents = true; // set overlap events to true
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnPlayerEnterPickupBox); // on the overlap of this call APickup OnPlayerEnterPickupBox function
	PickupBox->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root component of PickupRoot

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick( float DeltaTime ) // DeltaTime is consistent time across computers, tick is called every frame
{
	Super::Tick( DeltaTime );

	FVector NewLocation = GetActorLocation(); //create new vector equal to current actor location

	NewLocation.Z += (DeltaTime * 100.f); // Z is an axis value member of FVectors, multiply DeltaTime by 100 because it is very small number

	SetActorLocation(NewLocation); // set the actor location with an offset of Z - make the actors float

}

void APickup::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Destroy();
}

