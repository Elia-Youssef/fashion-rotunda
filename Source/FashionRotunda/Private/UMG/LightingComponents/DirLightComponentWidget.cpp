// Project by Rebel Art Studios.


#include "UMG/LightingComponents/DirLightComponentWidget.h"
#include "MannequinSystem/MannequinSubsystem.h"
#include "UMG/InputComponents/SliderInputWidget.h"

float UDirLightComponentWidget::FromPercentage(float Value, float Min, float Max)
{
	UE_LOG(LogTemp, Display, TEXT("FromPercentage: %f"), Value * (Max - Min) + Min);
	return Value * (Max - Min) + Min;
}

float UDirLightComponentWidget::ToPercentage(float Value, float Min, float Max)
{
	const float Clamped = FMath::Clamp(Value, Min, Max);
	return (Clamped - Min) / (Max - Min);
}


void UDirLightComponentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetGameInstance())
	{
		Subsystem = GetGameInstance()->GetSubsystem<UMannequinSubsystem>();
		if (!Subsystem) return;

		Intensity = Subsystem->GetSunIntensity();
		Pitch = Subsystem->GetSunPitch();
	}

	if (IntensityInput)
	{
		IntensityInput->OnSliderValueChanged.AddDynamic(this, &UDirLightComponentWidget::OnIntensityInputChanged);
		IntensityInput->SetValue(ToPercentage(Intensity, IntensityMin, IntensityMax));
	}
	if (PitchInput)
	{
		PitchInput->OnSliderValueChanged.AddDynamic(this, &UDirLightComponentWidget::OnPitchInputChanged);
		PitchInput->SetValue(ToPercentage(Pitch, PitchMin, PitchMax));
	}
}

void UDirLightComponentWidget::OnIntensityInputChanged(float Value)
{
	if (!Subsystem) return;
	Intensity = FromPercentage(Value, IntensityMin, IntensityMax);
	Subsystem->SetSunIntensity(Intensity);
}

void UDirLightComponentWidget::OnPitchInputChanged(float Value)
{
	if (!Subsystem) return;
	Pitch = FromPercentage(Value, PitchMin, PitchMax);
	Subsystem->SetSunPitch(Pitch);
}
