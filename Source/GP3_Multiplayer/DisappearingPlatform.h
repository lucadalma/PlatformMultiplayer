#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DisappearingPlatform.generated.h"

class UBoxComponent;

UCLASS()
class GP3_MULTIPLAYER_API ADisappearingPlatform : public AActor
{
    GENERATED_BODY()

public:
    ADisappearingPlatform();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* TriggerBox;

    UPROPERTY(ReplicatedUsing = OnRep_Disappear)
    bool bIsVisible = true;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION(Server, Reliable)
    void ServerDisappear();

    UFUNCTION()
    void OnRep_Disappear();

    void ResetPlatform();

    FTimerHandle ResetTimerHandle;

    FTimerHandle DelayBeforeDisappearHandle;

    UPROPERTY(EditAnywhere, Category = "Platform Timing")
    float TimeBeforeDisappear = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Platform Timing")
    float TimeBeforeReset = 3.0f;


public:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
