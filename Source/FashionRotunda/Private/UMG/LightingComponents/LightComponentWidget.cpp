// Project by Rebel Art Studios.


#include "UMG/LightingComponents/LightComponentWidget.h"

#include "Components/TextBlock.h"
#include "MannequinSystem/MannequinSubsystem.h"
#include "UMG/InputComponents/CheckboxInputWidget.h"
#include "UMG/InputComponents/SliderInputWidget.h"


FString ULightComponentWidget::FormatValue(float Value, const FString& Unit)
{
	return FString::Printf(TEXT("%.1f %s"), Value, *Unit);
}

float ULightComponentWidget::FromPercentage(float Value, float Min, float Max)
{
	return Value * (Max - Min) + Min;
}

float ULightComponentWidget::ToPercentage(float Value, float Min, float Max)
{
	const float Clamped = FMath::Clamp(Value, Min, Max);
	return (Clamped - Min) / (Max - Min);
}


void ULightComponentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetGameInstance())
	{
		Subsystem = GetGameInstance()->GetSubsystem<UMannequinSubsystem>();
	}

	if (CheckboxInput)
	{
		CheckboxInput->OnCheckBoxValueChanged.AddDynamic(this, &ULightComponentWidget::OnCheckboxInputChanged);
	}
	if (IntensityInput)
	{
		IntensityInput->OnSliderValueChanged.AddDynamic(this, &ULightComponentWidget::OnIntensityInputChanged);
	}
	if (TemperatureInput)
	{
		TemperatureInput->OnSliderValueChanged.AddDynamic(this, &ULightComponentWidget::OnTemperatureInputChanged);
	}
}

void ULightComponentWidget::SetupData(const FName& Tag)
{
	if (!Subsystem) return;

	LightTag = Tag;
	LightParams = Subsystem->GetStudioLightData(Tag);

	if (Label)
	{
		Label->SetText(FText::FromName(LightTag));
	}

	if (CheckboxInput)
	{
		CheckboxInput->SetValue(LightParams.bEnabled);
	}

	if (IntensityInput)
	{
		IntensityInput->SetValue(ToPercentage(LightParams.LightIntensity, IntensityMin, IntensityMax));
	}

	if (TemperatureInput)
	{
		TemperatureInput->SetValue(ToPercentage(LightParams.LightTemperature, TemperatureMin, TemperatureMax));
	}

	if (IntensityText)
	{
		IntensityText->SetText(FText::FromString(FormatValue(LightParams.LightIntensity, "cd")));
	}

	if (TemperatureText)
	{
		TemperatureText->SetText(FText::FromString(FormatValue(LightParams.LightTemperature, "k")));
	}
}

void ULightComponentWidget::OnCheckboxInputChanged(bool Value)
{
	if (!Subsystem) return;
	LightParams.bEnabled = Value;
	Subsystem->SetStudioLightData(LightTag, LightParams);
}

void ULightComponentWidget::OnIntensityInputChanged(float Value)
{
	if (!Subsystem) return;
	LightParams.LightIntensity = FromPercentage(Value, IntensityMin, IntensityMax);
	Subsystem->SetStudioLightData(LightTag, LightParams);

	if (!IntensityText) return;
	IntensityText->SetText(FText::FromString(FormatValue(LightParams.LightIntensity, "cd")));
}

void ULightComponentWidget::OnTemperatureInputChanged(float Value)
{
	if (!Subsystem) return;
	LightParams.LightTemperature = FromPercentage(Value, TemperatureMin, TemperatureMax);
	Subsystem->SetStudioLightData(LightTag, LightParams);

	if (!TemperatureText) return;
	TemperatureText->SetText(FText::FromString(FormatValue(LightParams.LightTemperature, "k")));
}
