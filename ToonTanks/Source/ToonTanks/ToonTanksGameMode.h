#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

class AToonTanksPlayerController;
class ABasePawn;

UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool Victory);

public:
	void OnActorDied(AActor* Unit);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Start Settings", meta = (AllowPrivateAccess = "true"))
	float GameStartTime = 3.0f;

	int32 EnemyTowerCount;

	UPROPERTY()
	AToonTanksPlayerController* ToonTanksPlayerController;
};