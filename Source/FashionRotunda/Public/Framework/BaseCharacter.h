// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class FASHIONROTUNDA_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	UPROPERTY(EditDefaultsOnly)
	bool bAllowInput = false;

protected:
	virtual void BeginPlay() override;

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;


	// Enhanced Input
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_LookAround;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_MoveAround;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_SwitchPawn;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UFUNCTION()
	void SwitchPawn();

	// Variables
	UPROPERTY()
	UCharacterMovementComponent* MovementComponent;
};
