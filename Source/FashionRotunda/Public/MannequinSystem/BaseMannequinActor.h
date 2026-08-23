// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseMannequinActor.generated.h"

class UArrowComponent;
class UCapsuleComponent;

UCLASS()
class FASHIONROTUNDA_API ABaseMannequinActor : public AActor
{
	GENERATED_BODY()

public:
	ABaseMannequinActor();

	UFUNCTION()
	void ToggleRotation();

	UFUNCTION()
	void ResetRotation();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void StartRotation();

	UFUNCTION()
	void PauseRotation();

	UFUNCTION()
	void Rotate();

private:
	// Components
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> CapsuleCollision;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UArrowComponent> ArrowComponent;

	// Rotation Variables
	FTimerHandle RotationTimer;

	UPROPERTY(EditDefaultsOnly)
	float RotationSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float TotalRotationTime = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float RotationInterval = 0.015f;

	float RotationDirection = 1.f;

	UPROPERTY()
	float InitialYaw = 0.f;

	UPROPERTY()
	float CurrentYaw = 0.f;

	bool bIsRotating = false;
	bool bShouldStop = false;
};
