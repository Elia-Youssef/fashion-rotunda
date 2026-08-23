// Project by Rebel Art Studios.


#include "UMG/ToolTipWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"

class UCanvasPanelSlot;

void UToolTipWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Text && !Tooltip.IsEmpty())
	{
		Text->SetText(Tooltip);
	}
}

void UToolTipWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!Container || !Container->Slot) return;

	UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Container->Slot);
	if (!PanelSlot) return;

	const FVector2D CanvasSize = Canvas->GetCachedGeometry().GetLocalSize() / 2.f;
	const FVector2D ContainerSize = Container->GetCachedGeometry().GetLocalSize() / 2.f;
	FVector2D SlotPosition = CanvasSize + ContainerSize + FVector2D{Margin, Margin};
	SlotPosition.X *= Position == ETooltipPosition::Right ? 1 : Position == ETooltipPosition::Left ? -1 : 0;
	SlotPosition.Y *= Position == ETooltipPosition::Top ? -1 : Position == ETooltipPosition::Bottom ? 1 : 0;
	PanelSlot->SetPosition(SlotPosition);
}

void UToolTipWidget::OnHover()
{
	if (Text->GetText().IsEmpty()) return;
	PlayAnimationForward(FadeAnimation);
}

void UToolTipWidget::OnUnhover()
{
	if (Text->GetText().IsEmpty()) return;
	PlayAnimationReverse(FadeAnimation);
}

void UToolTipWidget::SetText(const FText& TooltipText)
{
	if (!Text) return;
	Text->SetText(TooltipText);
}
