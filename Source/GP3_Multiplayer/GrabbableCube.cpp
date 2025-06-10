#include "GrabbableCube.h"
#include "Net/UnrealNetwork.h"

AGrabbableCube::AGrabbableCube()
{
    //Abilita la replicazione per questo actor
    bReplicates = true;
    //Abilita la replicazione del movimento per questo actor
    SetReplicateMovement(true);

    //crea e assegna la mesh
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
    //la mesh può essere replicata
    Mesh->SetIsReplicated(true);
    //Set up mesh
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Mesh->SetGenerateOverlapEvents(true);
}

//Registra le variabili che devono essere replicate
void AGrabbableCube::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    //Replica la variabile "GrabbedBy" su tutti i client
    DOREPLIFETIME(AGrabbableCube, GrabbedBy);
}
