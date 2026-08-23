// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DirLightComponentWidget.generated.h"


class USliderInputWidget;
class UMannequinSubsystem;

UCLASS()
class FASHIONROTUNDA_API UDirLightComponentWidget : public UUserWidget
{
	GENERATED_BODY()

	float Intensity = 0.f;
	float Pitch = 0.f;

	UPROPERTY()
	TObjectPtr<UMannequinSubsystem> Subsystem;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USliderInputWidget> IntensityInput;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USliderInputWidget> PitchInput;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnIntensityInputChanged(float Value);

	UFUNCTION()
	void OnPitchInputChanged(float Value);

	UPROPERTY(EditDefaultsOnly)
	float IntensityMin = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float IntensityMax = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float PitchMin = -180.f;

	UPROPERTY(EditDefaultsOnly)
	float PitchMax = 0.f;

private:
	static float FromPercentage(float Value, float Min, float Max);
	static float ToPercentage(float Value, float Min, float Max);
};
