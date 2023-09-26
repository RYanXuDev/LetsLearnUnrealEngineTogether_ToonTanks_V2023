#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnemyTower.generated.h"

class APlayerTank;

UCLASS()
class TOONTANKS_API AEnemyTower : public ABasePawn
{
	GENERATED_BODY()

public:
	AEnemyTower();
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void Die() override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	APlayerTank* PlayerTank;

	UPROPERTY(EditAnywhere, Category = "Fire", meta=(AllowPrivateAccess = "true"))
	float FireRange = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Fire", meta=(AllowPrivateAccess = "true"))
	float FireRate = 2.0f;
	
	FTimerHandle FireTimeHandle;
	
	void OnPlayerTankInFireRange();

	bool IsPlayerTankInFireRange() const;
};