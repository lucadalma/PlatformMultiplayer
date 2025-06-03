#include "DisappearingPlatform.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"

ADisappearingPlatform::ADisappearingPlatform()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;
    TriggerBox->SetCollisionProfileName("Trigger");
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADisappearingPlatform::OnOverlapBegin);
}

void ADisappearingPlatform::BeginPlay()
{
    Super::BeginPlay();
}

void ADisappearingPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    ACharacter* Character = Cast<ACharacter>(OtherActor);
    if (Character && HasAuthority() && bIsVisible)
    {
        GetWorldTimerManager().SetTimer(DelayBeforeDisappearHandle, this, &ADisappearingPlatform::ServerDisappear, TimeBeforeDisappear, false);
    }
}


void ADisappearingPlatform::ServerDisappear_Implementation()
{
    bIsVisible = false;
    OnRep_Disappear();

    GetWorldTimerManager().SetTimer(ResetTimerHandle, this, &ADisappearingPlatform::ResetPlatform, TimeBeforeReset, false);
}

void ADisappearingPlatform::OnRep_Disappear()
{
    SetActorHiddenInGame(!bIsVisible);
    SetActorEnableCollision(bIsVisible);
}

void ADisappearingPlatform::ResetPlatform()
{
    bIsVisible = true;
    OnRep_Disappear();
}

void ADisappearingPlatform::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ADisappearingPlatform, bIsVisible);
}
