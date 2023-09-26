#include "BasePawn.h"

#include "Components/CapsuleComponent.h"
#include "HealthComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));

	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));

	BaseMesh->SetupAttachment(CapsuleComponent);
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABasePawn::RotateTurret(const FVector& TargetLocation) const
{
	const FVector TargetDirection = TargetLocation - TurretMesh->GetComponentLocation();
	const FRotator TargetRotation = FRotator(0.0f, TargetDirection.Rotation().Yaw, 0.0f);

	TurretMesh->SetWorldRotation(TargetRotation);
}

void ABasePawn::Fire()
{
	GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass,
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation())->SetOwner(this);

	UGameplayStatics::SpawnSoundAtLocation(this, LaunchSound, ProjectileSpawnPoint->GetComponentLocation());
}

void ABasePawn::Die()
{
	ensure(DeathParticle);

	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), GetActorRotation());
	UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation());

	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShake);
}