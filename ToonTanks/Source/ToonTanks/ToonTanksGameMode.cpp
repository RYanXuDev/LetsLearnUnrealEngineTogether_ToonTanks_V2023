#include "ToonTanksGameMode.h"

#include "EnemyTower.h"
#include "PlayerTank.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	ensure(ToonTanksPlayerController);

	ToonTanksPlayerController->SetPlayerInputState(false);
	
	FTimerHandle GameStartTimerHandle;

	const FTimerDelegate GameStartTimerDelegate
		= FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerInputState, true);

	GetWorldTimerManager().SetTimer(GameStartTimerHandle, GameStartTimerDelegate, GameStartTime, false);
	
	GameStart();

	TArray<AActor*> EnemyTowers;

	UGameplayStatics::GetAllActorsOfClass(this, AEnemyTower::StaticClass(), EnemyTowers);
	EnemyTowerCount = EnemyTowers.Num();
}

void AToonTanksGameMode::OnActorDied(AActor* Unit)
{
	if (AEnemyTower* EnemyTower = Cast<AEnemyTower>(Unit))
	{
		EnemyTower->Die();
		
		EnemyTowerCount--;

		if (EnemyTowerCount <= 0)
		{
			GameOver(true);
		}
	}
	else if (APlayerTank* PlayerTank = Cast<APlayerTank>(Unit))
	{
		PlayerTank->Die();
		ToonTanksPlayerController->SetPlayerInputState(false);

		GameOver(false);
	}
}