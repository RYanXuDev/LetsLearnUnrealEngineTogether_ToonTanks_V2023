#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AToonTanksGameMode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

private:
	float Health;

	UPROPERTY(EditAnywhere, Category = "Health Settings", meta=(AllowPrivateAccess = "true"))
	float MaxHealth = 100.0f;

	UPROPERTY()
	AToonTanksGameMode* ToonTanksGameMode;
	
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};