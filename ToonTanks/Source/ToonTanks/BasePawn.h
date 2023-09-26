#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class AProjectile;
class UCapsuleComponent;
class UHealthComponent;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

protected:
	virtual void BeginPlay() override;

	void RotateTurret(const FVector& TargetLocation) const;

	void Fire();

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Fire", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "VFX", meta=(AllowPrivateAccess = "true"))
	UParticleSystem* DeathParticle;

	UPROPERTY(EditDefaultsOnly, Category = "VFX", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> DeathCameraShake;

	UPROPERTY(EditDefaultsOnly, Category = "SFX", meta=(AllowPrivateAccess = "true"))
	USoundBase* LaunchSound;

	UPROPERTY(EditDefaultsOnly, Category = "SFX", meta=(AllowPrivateAccess = "true"))
	USoundBase* DeathSound;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void Die();
};