// Project by Rebel Art Studios.

#include "UMG/InputComponents/SliderInputWidget.h"
#include "Components/Slider.h"

void USliderInputWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!InputSlider) return;

	InputSlider->OnValueChanged.AddUniqueDynamic(this, &ThisClass::OnInputChange);
}

void USliderInputWidget::OnInputChange(float Input)
{
	CurrentInput = Input;
	OnSliderValueChanged.Broadcast(Input);
}

void USliderInputWidget::SetValue(float Value)
{
	if (!InputSlider) return;
	CurrentInput = Value;
	InputSlider->SetValue(CurrentInput);
}

void USliderInputWidget::SetMaxValue(float MaxValue)
{
	if (!InputSlider) return;
	InputSlider->SetMaxValue(MaxValue);
}
