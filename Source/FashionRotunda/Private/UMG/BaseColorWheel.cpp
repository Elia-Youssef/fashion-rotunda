// Project by Rebel Art Studios.


#include "UMG/BaseColorWheel.h"
#include "Widgets/Colors/SColorWheel.h"

void UBaseColorWheel::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	SlateColorWheel.Reset();
}

TSharedRef<SWidget> UBaseColorWheel::RebuildWidget()
{
	TAttribute<FLinearColor> SelectedColorAttr = TAttribute<FLinearColor>::Create(
		TAttribute<FLinearColor>::FGetter::CreateLambda([this]() { return SelectedColor; })
	);

	TSharedRef<SColorWheel> Wheel = SNew(SColorWheel).SelectedColor(SelectedColorAttr).OnValueChanged(
			FOnLinearColorValueChanged::CreateUObject(this, &UBaseColorWheel::HandleSlateColorChanged));

	SlateColorWheel = Wheel;
	return Wheel;
}

void UBaseColorWheel::HandleSlateColorChanged(FLinearColor NewColor)
{
	SelectedColor = NewColor;
	OnColorChanged.Broadcast(NewColor);
}

void UBaseColorWheel::SetSelectedColor(FLinearColor NewColor)
{
	SelectedColor = NewColor;
}
