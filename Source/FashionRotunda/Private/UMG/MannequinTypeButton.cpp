// Project by Rebel Art Studios.


#include "UMG/MannequinTypeButton.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UMannequinTypeButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (MyButton)
	{
		MyButton->OnClicked.RemoveAll(this);
		MyButton->OnClicked.AddDynamic(this, &UMannequinTypeButton::HandleButtonClicked);
		MyButton->OnHovered.AddDynamic(this, &UMannequinTypeButton::OnButtonHover);
		MyButton->OnUnhovered.AddDynamic(this, & UMannequinTypeButton::OnButtonUnhover);
	}
	RefreshVisuals();
}

void UMannequinTypeButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

#if WITH_EDITOR

	// Preview
	if (IsDesignTime()) RefreshVisuals();

#endif
}

void UMannequinTypeButton::InitializeFromRow(const FMannequinTypes& InRow)
{
	RowData = InRow;
	RefreshVisuals();
}

void UMannequinTypeButton::HandleButtonClicked()
{
	OnClicked.Broadcast(RowData);
}

void UMannequinTypeButton::OnButtonHover()
{
	OnHovered.Broadcast(true, FText::FromName(RowData.DressName));
}

void UMannequinTypeButton::OnButtonUnhover()
{
	OnHovered.Broadcast(false, FText::FromName(RowData.DressName));
}

void UMannequinTypeButton::RefreshVisuals()
{
	if (MyImage)
	{
		if (RowData.Thumbnail)
		{
			MyImage->SetBrushFromTexture(RowData.Thumbnail, false);
		}
		else
		{
			const FSlateBrush Empty;
			MyImage->SetBrush(Empty);
		}
	}
}
