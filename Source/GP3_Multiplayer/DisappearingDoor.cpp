#include "DisappearingDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "DiseappiringDoorPlatform.h"

ADisappearingDoor::ADisappearingDoor()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;
}

void ADisappearingDoor::BeginPlay()
{
    Super::BeginPlay();
    UpdateDoorVisibility();
}

void ADisappearingDoor::NotifyPlateActivated(ADiseappiringDoorPlatform* Plate)
{
    if (!HasAuthority()) return;

    ActivePlates.Add(Plate);
    UpdateDoorVisibility();
}

void ADisappearingDoor::NotifyPlateDeactivated(ADiseappiringDoorPlatform* Plate)
{
    if (!HasAuthority()) return;

    ActivePlates.Remove(Plate);
    UpdateDoorVisibility();
}

void ADisappearingDoor::UpdateDoorVisibility()
{
    if (bHasBeenOpened)
    {
        // Porta già aperta, non cambia stato
        return;
    }

    bool bShouldBeVisible = ActivePlates.Num() < PlatesNeeded;

    if (!bShouldBeVisible && !bHasBeenOpened)
    {
        bHasBeenOpened = true;
        bIsVisible = false;

        // Chiamo la funzione di aggiornamento manualmente sul server
        OnRep_VisibilityChanged();
    }
}

void ADisappearingDoor::OnRep_VisibilityChanged()
{
    DoorMesh->SetVisibility(bIsVisible);
    SetActorHiddenInGame(!bIsVisible);
    SetActorEnableCollision(bIsVisible);
}

void ADisappearingDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ADisappearingDoor, bIsVisible);
    DOREPLIFETIME(ADisappearingDoor, bHasBeenOpened);
}
