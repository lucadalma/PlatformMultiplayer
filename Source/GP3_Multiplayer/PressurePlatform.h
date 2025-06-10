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
    //Costruttore
    APressurePlatform();

    //Tick
    virtual void Tick(float DeltaTime) override;

    //Attiva la piattaforma
    void ActivatePlatform();
    //Disattiva la piattaforma
    void DeactivatePlatform();

protected:
    //Begin
    virtual void BeginPlay() override;

private:
    //Posizione iniziale della piattaforma
    FVector StartLocation;
    //Posizione di destinazione
    FVector TargetLocation;

    //velocità di movimento
    UPROPERTY(EditAnywhere)
    float MoveSpeed = 200.0f;

    //bool per lo stato della piattaforma
    bool bIsActive = false;
};