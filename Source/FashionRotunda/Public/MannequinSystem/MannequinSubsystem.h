// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Utilities/Utilities.h"
#include "MannequinSubsystem.generated.h"

class ADirectionalLight;
class ABaseLightActor;

class ABaseMannequinActor;
struct FMannequinTypes;

USTRUCT(BlueprintType)
struct FCachedLightActors
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<ABaseLightActor*> Lights;
};

UCLASS()
class FASHIONROTUNDA_API UMannequinSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void AllowPlayerMovement();

	UFUNCTION()
	void SwitchPawnType();

	UFUNCTION()
	void RotateActor();

	UFUNCTION()
	void ResetActorRotation();

	UFUNCTION(BlueprintCallable)
	void SpawnItem(FMannequinTypes& Type);

	// Lights Controls
	void CacheStudioLights(const TArray<FName>& Tags);
	FExposedLightParams GetStudioLightData(const FName& Tag);
	void SetStudioLightData(const FName& Tag, const FExposedLightParams& LightParams);

	void SetSunIntensity(float Value);
	float GetSunIntensity();

	void SetSunPitch(float Value);
	float GetSunPitch();

	void SetMannequinMaterial(UMaterialInstance* Material);

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void RegisterInitialActor();

private:
	// Furniture Weak Pointer
	TWeakObjectPtr<ABaseMannequinActor> CurrentMannequin;

	FMannequinTypes CurrentRow;

	UPROPERTY()
	FTimerHandle TimerHandle;

	// Lights
	UPROPERTY()
	TMap<FName, FCachedLightActors> StudioLights;

	UPROPERTY()
	TObjectPtr<ADirectionalLight> DirectionalLight;

	UPROPERTY()
	TObjectPtr<UDirectionalLightComponent> DirectionalLightComp;

	UPROPERTY()
	FRotator InitialLightRotation;

	void SetDirectionalLight();
};
