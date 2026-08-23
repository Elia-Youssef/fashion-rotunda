// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SliderInputWidget.generated.h"

class USlider;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSliderValueChanged, float, Value);

UCLASS()
class FASHIONROTUNDA_API USliderInputWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> InputSlider;

	float CurrentInput;

public:
	FOnSliderValueChanged OnSliderValueChanged;

	void SetValue(float Value);
	void SetMaxValue(float MaxValue);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnInputChange(float Input);
};
