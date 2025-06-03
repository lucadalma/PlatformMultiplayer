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
    ADisappearingDoor();

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* DoorMesh;

    void NotifyPlateActivated(ADiseappiringDoorPlatform* Plate);
    void NotifyPlateDeactivated(ADiseappiringDoorPlatform* Plate);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(ReplicatedUsing = OnRep_VisibilityChanged)
    bool bIsVisible = true;

    UFUNCTION()
    void OnRep_VisibilityChanged();

    void UpdateDoorVisibility();

    UPROPERTY()
    TSet<ADiseappiringDoorPlatform*> ActivePlates;

    UPROPERTY(EditAnywhere)
    int PlatesNeeded = 2;

public:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    UPROPERTY(Replicated)
    bool bHasBeenOpened = false;
};
