#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PressurePlatform.h"
#include "PressurePlate.generated.h"


UCLASS()
class GP3_MULTIPLAYER_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	//Costruttore
	APressurePlate();

protected:
	//Begin
	virtual void BeginPlay() override;

public:	
	//Update
	virtual void Tick(float DeltaTime) override;

	//Componente Box Trigger che rileva le collisioni
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	//Riferimento alla piattaforma da attivare/disattivare
	UPROPERTY(EditAnywhere)
	APressurePlatform* PresPlatform;

	//Evento chiamato quando qualcosa entra nel TriggerBox
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Evento chiamato quando qualcosa esce nel TriggerBox
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
