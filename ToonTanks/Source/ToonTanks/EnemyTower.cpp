#include "EnemyTower.h"

#include "PlayerTank.h"
#include "Kismet/GameplayStatics.h"

AEnemyTower::AEnemyTower()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	ensure(PlayerTank);

	GetWorldTimerManager().SetTimer(FireTimeHandle, this, &AEnemyTower::OnPlayerTankInFireRange, FireRate, true);
}

void AEnemyTower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsPlayerTankInFireRange())
	{
		RotateTurret(PlayerTank->GetActorLocation());
	}
}

void AEnemyTower::OnPlayerTankInFireRange()
{
	if (!IsPlayerTankInFireRange())
	{
		return;
	}

	Fire();
}

bool AEnemyTower::IsPlayerTankInFireRange() const
{
	return FVector::Dist(GetActorLocation(), PlayerTank->GetActorLocation()) <= FireRange && PlayerTank->GetIsAlive();
}

void AEnemyTower::Die()
{
	Super::Die();
	
	Destroy();
}