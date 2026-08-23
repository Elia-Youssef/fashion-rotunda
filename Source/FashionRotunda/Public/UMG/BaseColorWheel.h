// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "BaseColorWheel.generated.h"

class SColorWheel;

// THIS RETURNS HS NOT RGB
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWheelColorChanged, FLinearColor, NewColor);

UCLASS()
class FASHIONROTUNDA_API UBaseColorWheel : public UWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor SelectedColor = FLinearColor::White;

	UPROPERTY(BlueprintAssignable)
	FOnWheelColorChanged OnColorChanged;

	UFUNCTION(BlueprintCallable)
	void SetSelectedColor(FLinearColor NewColor);

	UFUNCTION(BlueprintPure)
	FLinearColor GetSelectedColor() const { return SelectedColor; }

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

private:
	TSharedPtr<SColorWheel> SlateColorWheel;

	void HandleSlateColorChanged(FLinearColor NewColor);
};

