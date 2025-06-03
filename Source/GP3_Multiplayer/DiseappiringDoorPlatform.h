#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiseappiringDoorPlatform.generated.h"

UCLASS()
class GP3_MULTIPLAYER_API ADiseappiringDoorPlatform : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ADiseappiringDoorPlatform();

    UPROPERTY(EditAnywhere)
    class ADisappearingDoor* ConnectedDoor;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* TriggerBox;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
