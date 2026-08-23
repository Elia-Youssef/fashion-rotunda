// Project by Rebel Art Studios.

#include "UMG/LightingComponents/LightContainerWidget.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "MannequinSystem/MannequinSubsystem.h"
#include "UMG/LightingComponents/LightComponentWidget.h"
#include "Utilities/Utilities.h"

class UScrollBoxSlot;

void ULightContainerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetGameInstance())
	{
		Subsystem = GetGameInstance()->GetSubsystem<UMannequinSubsystem>();
	}

	PopulateWidget();
	SetRenderOpacity(0.f);
}

void ULightContainerWidget::PopulateWidget()
{
	if (!Container || !StudioLightsTable || !ComponentClass || !Subsystem) return;

	Container->ClearChildren();

	TArray<FName> LightTags;
	TArray<FStudioLights*> AllRows;
	StudioLightsTable->GetAllRows(TEXT("StudioLightsWidget"), AllRows);

	for (const FStudioLights* Row : AllRows)
	{
		if (!Row) continue;
		LightTags.AddUnique(Row->LightTag);
	}
	Subsystem->CacheStudioLights(LightTags);

	for (const FStudioLights* Row : AllRows)
	{
		if (!Row) continue;

		ULightComponentWidget* RowWidget = CreateWidget<ULightComponentWidget>(GetOwningPlayer(), ComponentClass);
		if (!RowWidget) continue;
		UPanelSlot* ChildSlot = Container->AddChild(RowWidget);
		RowWidget->SetupData(Row->LightTag);

		if (UScrollBoxSlot* ScrollSlot = Cast<UScrollBoxSlot>(ChildSlot))
		{
			ScrollSlot->SetPadding(FMargin(6.f, 2.f));
		}
	}
}
