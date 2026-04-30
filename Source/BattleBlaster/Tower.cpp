// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle FireTimerHandle;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsInFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::CheckFireCondition()
{
	if (Tank && IsInFireRange() )
	{
		Fire();
	}
}

bool ATower::IsInFireRange()
{
	bool Result = false;
	if (Tank)
	{
		float DistatnceToTank = FVector::Dist(GetActorLocation(),Tank->GetActorLocation());
		Result = (DistatnceToTank <= FireRange);

	}
	return Result;
}
