// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utilities/Utilities.h"
#include "BaseLightActor.generated.h"

class ULocalLightComponent;

UCLASS()
class FASHIONROTUNDA_API ABaseLightActor : public AActor
{
	GENERATED_BODY()

public:
	ABaseLightActor();

	UFUNCTION()
	void ControlLight();

	void SetLightData(const FExposedLightParams& Data);

	FExposedLightParams GetLightData() { return ExposedLightParams; };

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void RegisterLight();

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULocalLightComponent> MyLight;

	UPROPERTY(EditAnywhere)
	FHiddenLightParams HiddenLightParams;

	UPROPERTY(EditAnywhere)
	FExposedLightParams ExposedLightParams;

	UPROPERTY(EditAnywhere)
	FName LightTag = NAME_None;
};
