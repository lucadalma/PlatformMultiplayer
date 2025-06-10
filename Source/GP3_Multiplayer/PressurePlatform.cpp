#include "PressurePlatform.h"

APressurePlatform::APressurePlatform()
{
 	//Abilita il tick
	PrimaryActorTick.bCanEverTick = true;

}

//Begin
void APressurePlatform::BeginPlay()
{
	Super::BeginPlay();

    //Abilita la replicazione per il multiplayer
    if (HasAuthority()) {
        SetReplicates(true);
        SetReplicateMovement(true);
    }

    //Registra la posizione iniziale
	StartLocation = GetActorLocation();

    //Calcola la posizione finale
	TargetLocation = StartLocation + FVector(0, 0, 300);
}

//Tick
void APressurePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //Se la piattaforma è attiva muovi la piattaforma verso l’alto
    if (bIsActive)
    {
        FVector CurrentLocation = GetActorLocation();
        FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
        SetActorLocation(NewLocation);
    }
    //Altrimenti torna giù
    else
    {
        FVector CurrentLocation = GetActorLocation();
        FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, StartLocation, DeltaTime, MoveSpeed);
        SetActorLocation(NewLocation);
    }
}

//Attiva la piattaforma
void APressurePlatform::ActivatePlatform()
{
    bIsActive = true;
}

//Disattiva la piattaforma
void APressurePlatform::DeactivatePlatform()
{
    bIsActive = false;
}

