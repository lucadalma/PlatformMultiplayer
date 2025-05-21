// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlatform.generated.h"

UCLASS()
class GP3_MULTIPLAYER_API APressurePlatform : public AActor
{
    GENERATED_BODY()

public:
    APressurePlatform();

    virtual void Tick(float DeltaTime) override;

    void ActivatePlatform();
    void DeactivatePlatform();

protected:
    virtual void BeginPlay() override;

private:
    FVector StartLocation;
    FVector TargetLocation;

    UPROPERTY(EditAnywhere)
    float MoveSpeed = 200.0f;

    bool bIsActive = false;
};