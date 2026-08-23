// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/Utilities.h"
#include "LightContainerWidget.generated.h"

class ULightComponentWidget;
class UScrollBox;
class USliderInputWidget;
class UCheckboxInputWidget;
class UTextBlock;
class UMannequinSubsystem;

UCLASS()
class FASHIONROTUNDA_API ULightContainerWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> StudioLightsTable;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULightComponentWidget> ComponentClass;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScrollBox> Container;

	UPROPERTY()
	TObjectPtr<UMannequinSubsystem> Subsystem;

protected:
	virtual void NativeConstruct() override;

	void PopulateWidget();
};
