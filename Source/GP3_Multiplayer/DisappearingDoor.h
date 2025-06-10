#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DisappearingDoor.generated.h"

class ADiseappiringDoorPlatform;

UCLASS()
class GP3_MULTIPLAYER_API ADisappearingDoor : public AActor
{
    GENERATED_BODY()

public:
    //costruttore
    ADisappearingDoor();

    //Mesh
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* DoorMesh;

    //Chiamata da una piattaforma quando attivata
    void NotifyPlateActivated(ADiseappiringDoorPlatform* Plate);
    //Chiamata da una piattaforma quando disattivata
    void NotifyPlateDeactivated(ADiseappiringDoorPlatform* Plate);

protected:
    virtual void BeginPlay() override;
    //Visibilitò della porta, replicata nel client
    UPROPERTY(ReplicatedUsing = OnRep_VisibilityChanged)
    bool bIsVisible = true;

    //Funzione chiamata automaticamente quando bIsVisible cambia su client
    UFUNCTION()
    void OnRep_VisibilityChanged();

    //Gestisco logica di apertura porta
    void UpdateDoorVisibility();

    //Elenco delle piattaforme attive
    UPROPERTY()
    TSet<ADiseappiringDoorPlatform*> ActivePlates;

    //Numero di piattaforme attive per aprire la porta
    UPROPERTY(EditAnywhere)
    int PlatesNeeded = 2;

public:
    //Variabili da replicare
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    //Serve per evitare che la porta venga aperta più volte
    UPROPERTY(Replicated)
    bool bHasBeenOpened = false;
};
