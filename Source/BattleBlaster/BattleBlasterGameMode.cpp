// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(),Towers);
	TowerCount = Towers.Num();
	
	UE_LOG(LogTemp,Log,TEXT("TowerCount:%d"),TowerCount);
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if (PlayerPawn)
	{
		Tank = Cast<ATank>(PlayerPawn);
		if (!Tank)
		{
			UE_LOG(LogTemp,Error,TEXT("Tank could not be found"));
		}
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("PlayerPawn not found"));
	}
	
	int32 LoopIndex = 0;
	
	while (LoopIndex < TowerCount)
	{
		if (AActor* TowerActor = Towers[LoopIndex])
		{
			if (ATower* Tower = Cast<ATower>(TowerActor))
			{
				Tower->Tank = Tank;
				UE_LOG(LogTemp,Log,TEXT("Tower:%s"),*Tower->GetActorNameOrLabel());
			}
		}
		LoopIndex++;
	}
}

void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{
	bool IsGameOver = false;
	
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		IsGameOver = true;
	}
	else
	{
		//A Tower just died
		ATower* DeadTower = Cast<ATower>(DeadActor);
		if (DeadTower)
		{
			//
			DeadTower->HandleDestruction();
			TowerCount--;
			if (TowerCount == 0)
			{
				IsVictory = true;		
				IsGameOver = true;
			}
		}
	}
	if (IsGameOver)
	{
		FString GameOverString = IsVictory ? "Victory" : "Defeat";
		UE_LOG(LogTemp, Display, TEXT("Game Over: %s"), *GameOverString);
		FTimerHandle GameOverTimerHandle;
		GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ABattleBlasterGameMode::OnGameOverTimerTimeout,GameOverDelay, false);
	}
}

void ABattleBlasterGameMode::OnGameOverTimerTimeout()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	if (IsVictory)
	{
		
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), *CurrentLevelName);
	}
}
