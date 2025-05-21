// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "TimerManager.h"
#include "MultiplayerGameInstance.h"

void ALobbyGameMode::StartGame()
{
	auto GameInstance = Cast<UMultiplayerGameInstance>(GetGameInstance());

	if (GameInstance == nullptr) return;

	GameInstance->StartSession();

	UWorld* World = GetWorld();

	if (World == nullptr) return;

	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NumberOfPlayer++;

	if (NumberOfPlayer >= 2)
	{
		GetWorldTimerManager().SetTimer(GameStartTimer, this, &ALobbyGameMode::StartGame, 10);
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	NumberOfPlayer--;
}
