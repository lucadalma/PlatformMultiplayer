#include "DiseappiringDoorPlatform.h"
#include "DisappearingDoor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

ADiseappiringDoorPlatform::ADiseappiringDoorPlatform()
{
    //Non serve il tick
    PrimaryActorTick.bCanEverTick = false;  

    //Crea il trigger box
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    //Set up della trigger box
    TriggerBox->SetCollisionProfileName("Trigger");
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADiseappiringDoorPlatform::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADiseappiringDoorPlatform::OnOverlapEnd);
}

void ADiseappiringDoorPlatform::BeginPlay()
{
    Super::BeginPlay();
}

//On trigger Enter
void ADiseappiringDoorPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Solo il server può modificare lo stato, e solo se c'è una porta collegata
    if (HasAuthority() && ConnectedDoor && Cast<ACharacter>(OtherActor))
    {
        //Notifica alla porta che questa piattaforma è stata attivata
        ConnectedDoor->NotifyPlateActivated(this);
    }
}

//On trigger exit
void ADiseappiringDoorPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (HasAuthority() && ConnectedDoor && Cast<ACharacter>(OtherActor))
    {
        //Notifica alla porta che questa piattaforma è stata disattivata
        ConnectedDoor->NotifyPlateDeactivated(this);
    }
}
