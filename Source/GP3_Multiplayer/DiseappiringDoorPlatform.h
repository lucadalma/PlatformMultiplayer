#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiseappiringDoorPlatform.generated.h"

UCLASS()
class GP3_MULTIPLAYER_API ADiseappiringDoorPlatform : public AActor
{
    GENERATED_BODY()

public:
    //Costuttore
    ADiseappiringDoorPlatform();

    //Porta collegata che sarà quella da disattivare
    UPROPERTY(EditAnywhere)
    class ADisappearingDoor* ConnectedDoor;

protected:
    virtual void BeginPlay() override;

    //Trigger box per rilevare se il player è sopra la pedana
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* TriggerBox;

    //Funzione chiamata quando un attore entra nel trigger
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    //Funzione chiamata quando un attore esce dal trigger
    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
