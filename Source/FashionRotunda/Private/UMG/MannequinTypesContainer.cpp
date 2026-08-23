// Project by Rebel Art Studios.


#include "UMG/MannequinTypesContainer.h"

#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "UMG/MannequinTypeButton.h"
#include "UMG/ToolTipWidget.h"
#include "Utilities/Utilities.h"

void UMannequinTypesContainer::NativeConstruct()
{
	Super::NativeConstruct();

	PopulateWidget();
}

void UMannequinTypesContainer::SynchronizeProperties()
{
	Super::SynchronizeProperties();

#if WITH_EDITOR

	// Preview
	if (IsDesignTime()) PopulateWidget();

#endif
}

void UMannequinTypesContainer::PopulateWidget()
{
	if (!MyDataTable || !ButtonClass || !MyScrollBox) return;

	MyScrollBox->ClearChildren();

	TArray<FName> RowNames = MyDataTable->GetRowNames();

	for (const FName& RowName : RowNames)
	{
		if (const FMannequinTypes* RowPtr = MyDataTable->FindRow<FMannequinTypes>(RowName, "PopulateWidget"))
		{
			UMannequinTypeButton* Entry = CreateWidget<UMannequinTypeButton>(this, ButtonClass);
			if (!Entry) continue;

			Entry->InitializeFromRow(*RowPtr);
			Entry->OnClicked.AddUniqueDynamic(this, &UMannequinTypesContainer::HandleButtonClicked);
			Entry->OnHovered.AddUniqueDynamic(this, &UMannequinTypesContainer::HandleButtonHovered);
			UPanelSlot* ChildSlot = MyScrollBox->AddChild(Entry);

			if (UScrollBoxSlot* ScrollSlot = Cast<UScrollBoxSlot>(ChildSlot))
			{
				ScrollSlot->SetPadding(FMargin(2.f));
			}
		}
	}
}

void UMannequinTypesContainer::HandleButtonClicked(const FMannequinTypes& ClickedRow)
{
	OnTypeSelected.Broadcast(ClickedRow);
}

void UMannequinTypesContainer::HandleButtonHovered(bool bIsHovering, FText Text)
{
	if (!CustomTooltip) return;

	CustomTooltip->SetText(Text);

	if (bIsHovering) CustomTooltip->OnHover();
	else CustomTooltip->OnUnhover();
}
