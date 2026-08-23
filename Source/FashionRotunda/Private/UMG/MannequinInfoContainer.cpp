// Project by Rebel Art Studios.


#include "UMG/MannequinInfoContainer.h"

#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableText.h"

void UMannequinInfoContainer::NativeConstruct()
{
	Super::NativeConstruct();

	if (RotateButton)
	{
		RotateButton->OnClicked.RemoveAll(this);
		RotateButton->OnClicked.AddDynamic(this, &UMannequinInfoContainer::RotateButtonPressed);
	}

	if (ResetButton)
	{
		ResetButton->OnClicked.RemoveAll(this);
		ResetButton->OnClicked.AddDynamic(this, &UMannequinInfoContainer::ResetRotationButtonPressed);
	}

	if (AudioButton)
	{
		AudioButton->OnClicked.RemoveAll(this);
		AudioButton->OnClicked.AddDynamic(this, &UMannequinInfoContainer::AudioButtonPressed);
	}

	if (MaterialButton)
	{
		MaterialButton->OnClicked.AddUniqueDynamic(this, &UMannequinInfoContainer::MaterialButtonPressed);
	}
}

void UMannequinInfoContainer::PopulateInfo(const FMannequinTypes& Types)
{
	CurrentType = Types;

	if (DressImage)
	{
		if (CurrentType.Thumbnail)
		{
			DressImage->SetBrushFromTexture(CurrentType.Thumbnail, false);
		}
		else
		{
			FSlateBrush EmptyBrush;
			DressImage->SetBrush(EmptyBrush);
		}
	}

	if (DressName)
	{
		DressName->SetText(FText::FromName(CurrentType.DressName));
	}

	if (DressInfo)
	{
		if (!CurrentType.Description.IsEmpty())
		{
			DressInfo->SetText(CurrentType.Description);
		}
		else
		{
			DressInfo->SetText(FText::FromName(CurrentType.DressName));
		}
	}

	if (!MaterialsContainer || !MaterialSelectorClass) return;
	MaterialsContainer->ClearChildren();

	for (FMannequinMaterial& Material : CurrentType.Materials)
	{
		if (UMaterialSelectorWidget* Selector = CreateWidget<UMaterialSelectorWidget>(this, MaterialSelectorClass))
		{
			Selector->SetValue(Material);
			Selector->OnMaterialSelected.AddUniqueDynamic(this, &ThisClass::OnMaterialSelectorClicked);
			UPanelSlot* ChildSlot = MaterialsContainer->AddChild(Selector);
			if (UHorizontalBoxSlot* HbSlot = Cast<UHorizontalBoxSlot>(ChildSlot))
			{
				HbSlot->SetSize(FSlateChildSize{ESlateSizeRule::Type::Fill});
				HbSlot->SetHorizontalAlignment(HAlign_Center);
				HbSlot->SetVerticalAlignment(VAlign_Center);
			}
		}
	}
}

void UMannequinInfoContainer::RotateButtonPressed()
{
	OnRotateSelected.Broadcast();
}

void UMannequinInfoContainer::ResetRotationButtonPressed()
{
	OnResetRotationSelected.Broadcast();
}

void UMannequinInfoContainer::AudioButtonPressed()
{
	OnAudioSelected.Broadcast(CurrentType);
}

void UMannequinInfoContainer::MaterialButtonPressed()
{
	if (!MaterialsContainer || !MaterialSelectorClass) return;
	if (MaterialsContainer->GetVisibility() == ESlateVisibility::Collapsed)
	{
		MaterialsContainer->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		MaterialsContainer->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMannequinInfoContainer::OnMaterialSelectorClicked(UMaterialInstance* Material)
{
	OnMaterialSelected.Broadcast(Material);
}
