#include "PushableObject.h"
#include "Net/UnrealNetwork.h"

APushableObject::APushableObject()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;
    SetReplicateMovement(true);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    if (HasAuthority())
    {
        Mesh->SetSimulatePhysics(true);
    }
    else
    {
        Mesh->SetSimulatePhysics(false);
    }

    Mesh->SetCollisionProfileName("PhysicsActor");

    Mesh->OnComponentHit.AddDynamic(this, &APushableObject::OnHit);
}

void APushableObject::BeginPlay()
{
    Super::BeginPlay();
}

void APushableObject::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Optional: Debug o effetti sonori
    // UE_LOG(LogTemp, Warning, TEXT("Object hit by %s"), *OtherActor->GetName());
}

void APushableObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //DOREPLIFETIME(APushableObject, Mesh);
}
