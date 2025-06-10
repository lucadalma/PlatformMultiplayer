#include "PressurePlate.h"
#include "GameFramework/Character.h"

//Costruttore
APressurePlate::APressurePlate()
{
	//Abilita il tick
	PrimaryActorTick.bCanEverTick = true;

	//crea il trigger e set up
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

}

//Begin
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	//Assicura che l’attore sia replicato correttamente in multiplayer (solo lato server)
	if (HasAuthority()) 
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	//Funzioni del trigger
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);

}

//Tick
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Quando un attore entra nel box trigger
void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Controlla che l'attore sia un character
	if (OtherActor && OtherActor->IsA<ACharacter>())
	{
		//Se c’è una piattaforma assegnata la attiva
		if (PresPlatform)
		{
			PresPlatform->ActivatePlatform();
		}
	}
}

//Quando un attore esce dal box trigger
void APressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Controlla che l'attore sia un character
	if (OtherActor && OtherActor->IsA<ACharacter>())
	{
		//Se c’è una piattaforma assegnata la disattiva
		if (PresPlatform)
		{
			PresPlatform->DeactivatePlatform();
		}
	}
}

