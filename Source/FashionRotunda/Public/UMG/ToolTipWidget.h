// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToolTipWidget.generated.h"

class UCanvasPanel;
class UOverlay;

UENUM(BlueprintType)
enum class ETooltipPosition : uint8
{
	Left,
	Right,
	Top,
	Bottom,
	Center
};

class UTextBlock;

UCLASS()
class FASHIONROTUNDA_API UToolTipWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Canvas;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> Container;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FadeAnimation;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	ETooltipPosition Position = ETooltipPosition::Right;

	UPROPERTY(EditAnywhere)
	FText Tooltip;

	UPROPERTY(EditAnywhere)
	float Margin = 0.f;

	void OnHover();
	void OnUnhover();

	void SetText(const FText& TooltipText);
};
