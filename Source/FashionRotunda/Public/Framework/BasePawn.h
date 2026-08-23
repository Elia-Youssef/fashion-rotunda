// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;

UCLASS()
class FASHIONROTUNDA_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

	UPROPERTY(EditDefaultsOnly)
	bool bAllowInput = false;

protected:
	virtual void BeginPlay() override;

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Components
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;

	//Enhanced Input
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> IMC;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_Orbit;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_Zoom;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_Pan;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_SwitchPawn;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> RightClickAction;

	UFUNCTION()
	void Orbit(const FInputActionValue& Value);

	UFUNCTION()
	void Zoom(const FInputActionValue& Value);

	UFUNCTION()
	void Pan(const FInputActionValue& Value);

	UFUNCTION()
	void SwitchPawn();

	UFUNCTION()
	void OnRightClickStarted(const FInputActionValue& Value);

	UFUNCTION()
	void OnRightClickCompleted(const FInputActionValue& Value);

	// Variables
	UPROPERTY(EditDefaultsOnly)
	float InitialSpringArmLength = 300.f;

	UPROPERTY()
	float CurrentSpringArmLength = InitialSpringArmLength;

	UPROPERTY(EditDefaultsOnly)
	FVector2D SpringArmRange = FVector2D::ZeroVector;

	UPROPERTY(EditDefaultsOnly)
	float StepSize = 20.f;

	UPROPERTY(EditDefaultsOnly)
	float PanSpeed = 20.f;

	bool bRightClickDown = false;
};
