#include "DisappearingDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "DiseappiringDoorPlatform.h"

ADisappearingDoor::ADisappearingDoor()
{
    PrimaryActorTick.bCanEverTick = false;
    //Replicazione
    bReplicates = true;

    //Crea Mesh
    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;
}

void ADisappearingDoor::BeginPlay()
{
    Super::BeginPlay();
    //Visibilità iniziale
    UpdateDoorVisibility();
}

//Piattaforma attivata
void ADisappearingDoor::NotifyPlateActivated(ADiseappiringDoorPlatform* Plate)
{
    //Solo il server può modificare lo stato
    if (!HasAuthority()) return;

    //Aggiunge la piattaforma alla lista
    ActivePlates.Add(Plate);
    //Aggiorna visibilità in base al nuovo stato
    UpdateDoorVisibility();
}

//Piattaforma disattivata
void ADisappearingDoor::NotifyPlateDeactivated(ADiseappiringDoorPlatform* Plate)
{
    //Se non è server = return
    if (!HasAuthority()) return;

    //Rimuove la piattaforma
    ActivePlates.Remove(Plate);
    UpdateDoorVisibility();
}

void ADisappearingDoor::UpdateDoorVisibility()
{
    //Se la porta è già stata aperta, non fare nulla
    if (bHasBeenOpened)
    {
        return;
    }

    //Se non sono ancora abbastanza piastre attive, la porta rimane visibile 
    bool bShouldBeVisible = ActivePlates.Num() < PlatesNeeded;

    //Se è il momento di aprire la porta
    if (!bShouldBeVisible && !bHasBeenOpened)
    {
        //Segna come già aperta per non riaprire
        bHasBeenOpened = true;
        //Nasconde la porta
        bIsVisible = false;
        //Aggiorna 
        OnRep_VisibilityChanged();
    }
}

void ADisappearingDoor::OnRep_VisibilityChanged()
{
    //Mostra o nasconde la mesh
    DoorMesh->SetVisibility(bIsVisible);
    //Nasconde l'attore
    SetActorHiddenInGame(!bIsVisible);
    //attiva o disattiva le collisioni
    SetActorEnableCollision(bIsVisible);
}

void ADisappearingDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //Indica che bIsVisible e bHasBeenOpened devono essere replicati
    DOREPLIFETIME(ADisappearingDoor, bIsVisible);
    DOREPLIFETIME(ADisappearingDoor, bHasBeenOpened);
}
