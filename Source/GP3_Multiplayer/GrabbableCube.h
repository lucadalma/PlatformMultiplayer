#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrabbableCube.generated.h"

UCLASS()
class GP3_MULTIPLAYER_API AGrabbableCube : public AActor
{
    GENERATED_BODY()

public:

    //Costruttore
    AGrabbableCube();

protected:
    //Funzione per specificare le variabili da replicare
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
    //La mesh del cubo
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    //Player che attualmente ha preso il cubo
    //Replicated = replicato su tutti i client
    UPROPERTY(Replicated)
    AActor* GrabbedBy;
};
