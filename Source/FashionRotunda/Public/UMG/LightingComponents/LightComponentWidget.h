// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/Utilities.h"
#include "LightComponentWidget.generated.h"


class USliderInputWidget;
class UCheckboxInputWidget;
class UTextBlock;
class UMannequinSubsystem;

UCLASS()
class FASHIONROTUNDA_API ULightComponentWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetupData(const FName& Tag);

	FName LightTag = NAME_None;

	FExposedLightParams LightParams;

	UPROPERTY()
	TObjectPtr<UMannequinSubsystem> Subsystem;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Label;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckboxInputWidget> CheckboxInput;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USliderInputWidget> IntensityInput;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> IntensityText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USliderInputWidget> TemperatureInput;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TemperatureText;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnCheckboxInputChanged(bool Value);

	UFUNCTION()
	void OnIntensityInputChanged(float Value);

	UFUNCTION()
	void OnTemperatureInputChanged(float Value);

	UPROPERTY(EditDefaultsOnly)
	float IntensityMin = 0.f;

	UPROPERTY(EditDefaultsOnly)
	float IntensityMax = 20.f;

	UPROPERTY(EditDefaultsOnly)
	float TemperatureMin = 1000.f;

	UPROPERTY(EditDefaultsOnly)
	float TemperatureMax = 15000.f;

private:
	FString FormatValue(float Value, const FString& Unit);
	float FromPercentage(float Value, float Min, float Max);
	float ToPercentage(float Value, float Min, float Max);
};
