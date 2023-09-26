#include "PlayerTank.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"

APlayerTank::APlayerTank()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void APlayerTank::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		ensure(Subsystem);

		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(GameplayMappingContext, 0);
	}

	IsAlive = true;
}

void APlayerTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	ensure(EnhancedInputComponent && MoveInputAction && TurnInputAction && FireInputAction);

	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &APlayerTank::Move);
	EnhancedInputComponent->BindAction(TurnInputAction, ETriggerEvent::Triggered, this, &APlayerTank::Turn);
	EnhancedInputComponent->BindAction(FireInputAction, ETriggerEvent::Triggered, this, &APlayerTank::Fire);
}

void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (const APlayerController* PlayerTankController = Cast<APlayerController>(GetController()))
	{
		FHitResult CursorHitResult;
		PlayerTankController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHitResult);
		// GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, CursorHitResult.ImpactPoint.ToString());
		RotateTurret(CursorHitResult.ImpactPoint);
	}
}

void APlayerTank::Move(const FInputActionValue& InputActionValue)
{
	if (InputActionValue.Get<float>() != 0.0f)
	{
		FVector MoveDelta(0.0f);

		MoveDelta.X = InputActionValue.Get<float>() * MoveSpeed * GetWorld()->GetDeltaSeconds();
		
		AddActorLocalOffset(MoveDelta);
	}
}

void APlayerTank::Turn(const FInputActionValue& InputActionValue)
{
	// GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, InputActionValue.ToString());

	if (InputActionValue.Get<float>() != 0.0f)
	{
		FRotator DeltaRotation = FRotator::ZeroRotator;

		DeltaRotation.Yaw = InputActionValue.Get<float>() * TurnSpeed * GetWorld()->GetDeltaSeconds();
		AddActorLocalRotation(DeltaRotation);
	}
}

void APlayerTank::Die()
{
	Super::Die();

	IsAlive = false;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}