#include "HealthComponent.h"

#include "ToonTanksGameMode.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	ToonTanksGameMode = Cast<AToonTanksGameMode>(GetWorld()->GetAuthGameMode());

	Health = MaxHealth;
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);
}

void UHealthComponent::OnTakeDamage(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)
{
	if (Health <= 0.0f)
	{
		return;
	}
	
	Health -= Damage;

	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
	// 	FString::Printf(TEXT("%s Current Health: %f"), *GetOwner()->GetActorNameOrLabel(), Health));
 
	if (Health <= 0.0f)
	{
		// Cast<ABasePawn>(GetOwner())->Die();
		ToonTanksGameMode->OnActorDied(DamagedActor);
	}
}