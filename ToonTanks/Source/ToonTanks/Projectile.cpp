#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	TrailParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle"));
	TrailParticleComponent->SetupAttachment(MeshComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}
void AProjectile::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse,
	const FHitResult& HitResult)
{
	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetOwner()->GetInstigatorController(), this, UDamageType::StaticClass());

	ensure(HitParticle);
	
	UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, HitResult.ImpactPoint, NormalImpulse.Rotation());
	UGameplayStatics::SpawnSoundAtLocation(this, HitSound, HitResult.ImpactPoint);

	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShake);
	
	Destroy();
}