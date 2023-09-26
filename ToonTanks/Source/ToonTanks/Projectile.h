#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	AProjectile();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* TrailParticleComponent;

	UPROPERTY(EditDefaultsOnly, Category = "VFX", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* HitParticle;

	UPROPERTY(EditDefaultsOnly, Category = "VFX", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> HitCameraShake;
	
	UPROPERTY(EditDefaultsOnly, Category = "SFX", meta = (AllowPrivateAccess = "true"))
	USoundBase* HitSound;
	
	UPROPERTY(EditAnywhere, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float Damage = 10.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult);
};