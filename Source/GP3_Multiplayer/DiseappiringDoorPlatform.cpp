#include "DiseappiringDoorPlatform.h"
#include "DisappearingDoor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

ADiseappiringDoorPlatform::ADiseappiringDoorPlatform()
{
    PrimaryActorTick.bCanEverTick = false;  // Non serve il tick

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionProfileName("Trigger");
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADiseappiringDoorPlatform::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADiseappiringDoorPlatform::OnOverlapEnd);
}

void ADiseappiringDoorPlatform::BeginPlay()
{
    Super::BeginPlay();
}

void ADiseappiringDoorPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (HasAuthority() && ConnectedDoor && Cast<ACharacter>(OtherActor))
    {
        ConnectedDoor->NotifyPlateActivated(this);
    }
}

void ADiseappiringDoorPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (HasAuthority() && ConnectedDoor && Cast<ACharacter>(OtherActor))
    {
        ConnectedDoor->NotifyPlateDeactivated(this);
    }
}
