#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "PlayerTank.generated.h"

class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;

UCLASS()
class TOONTANKS_API APlayerTank : public ABasePawn
{
	GENERATED_BODY()

public:
	APlayerTank();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
    USpringArmComponent* SpringArmComponent;
    
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
    UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input", meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* GameplayMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveInputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* TurnInputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* FireInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta=(AllowPrivateAccess = "true"))
	float MoveSpeed = 500.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta=(AllowPrivateAccess = "true"))
	float TurnSpeed = 100.0f;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void Die() override;

	bool GetIsAlive() const { return IsAlive; }

private:
	bool IsAlive = true;
	
	void Move(const FInputActionValue& InputActionValue);
	
	void Turn(const FInputActionValue& InputActionValue);
};