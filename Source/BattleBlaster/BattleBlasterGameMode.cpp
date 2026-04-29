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
