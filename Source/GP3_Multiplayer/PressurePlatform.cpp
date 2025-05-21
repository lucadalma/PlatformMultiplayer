// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlatform.h"

// Sets default values
APressurePlatform::APressurePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APressurePlatform::BeginPlay()
{
	Super::BeginPlay();

    if (HasAuthority()) {
        SetReplicates(true);
        SetReplicateMovement(true);
    }

	StartLocation = GetActorLocation();
	TargetLocation = StartLocation + FVector(0, 0, 300);
}

// Called every frame
void APressurePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bIsActive)
    {
        FVector CurrentLocation = GetActorLocation();
        FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
        SetActorLocation(NewLocation);
    }
    else
    {
        // Torna giù (opzionale)
        FVector CurrentLocation = GetActorLocation();
        FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, StartLocation, DeltaTime, MoveSpeed);
        SetActorLocation(NewLocation);
    }
}

void APressurePlatform::ActivatePlatform()
{
    bIsActive = true;
}

void APressurePlatform::DeactivatePlatform()
{
    bIsActive = false;
}

