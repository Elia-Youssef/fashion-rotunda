// Project by Rebel Art Studios.


#include "UMG/MaterialSelectorWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "UMG/ToolTipWidget.h"

void UMaterialSelectorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button)
	{
		Button->OnClicked.AddUniqueDynamic(this, &ThisClass::OnButtonClick);
		Button->OnHovered.AddUniqueDynamic(this, &ThisClass::OnButtonHovered);
		Button->OnUnhovered.AddUniqueDynamic(this, &ThisClass::OnButtonUnhovered);
	}
}

void UMaterialSelectorWidget::SetValue(const FMannequinMaterial& Material)
{
	Data = Material;
	if (Image && Material.Texture)
	{
		Image->SetBrushFromTexture(Material.Texture);
	}
	if (CustomTooltip)
	{
		CustomTooltip->SetText(Material.Tooltip);
	}
}

void UMaterialSelectorWidget::OnButtonClick()
{
	OnMaterialSelected.Broadcast(Data.Material);
}

void UMaterialSelectorWidget::OnButtonHovered()
{
	if (!CustomTooltip) return;
	CustomTooltip->OnHover();
}

void UMaterialSelectorWidget::OnButtonUnhovered()
{
	if (!CustomTooltip) return;
	CustomTooltip->OnUnhover();
}
