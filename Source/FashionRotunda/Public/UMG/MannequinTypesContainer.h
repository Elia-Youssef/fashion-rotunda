// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/Utilities.h"
#include "MannequinTypesContainer.generated.h"


class UToolTipWidget;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMannequinTypeSelected, FMannequinTypes, SelectedType);

class UScrollBox;
class UMannequinTypeButton;

UCLASS()
class FASHIONROTUNDA_API UMannequinTypesContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void PopulateWidget();

	UPROPERTY()
	FOnMannequinTypeSelected OnTypeSelected;

protected:
	virtual void NativeConstruct() override;
	virtual void SynchronizeProperties() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UToolTipWidget> CustomTooltip;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> MyDataTable = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScrollBox> MyScrollBox = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMannequinTypeButton> ButtonClass;

	UFUNCTION()
	void HandleButtonClicked(const FMannequinTypes& ClickedRow);

	UFUNCTION()
	void HandleButtonHovered(bool bIsHovering, FText Text);
};
