// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/Utilities.h"
#include "MannequinTypeButton.generated.h"

class UImage;
class UButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMannequinButtonClicked, const FMannequinTypes&, MannequinTypes);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMannequinButtonHovered, bool, IsHovering, FText, Text);


UCLASS()
class FASHIONROTUNDA_API UMannequinTypeButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void InitializeFromRow(const FMannequinTypes& InRow);

	FOnMannequinButtonClicked OnClicked;
	
	FOnMannequinButtonHovered OnHovered;

	UFUNCTION(BlueprintPure)
	const FMannequinTypes& GetRow() const { return RowData; }

protected:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

private:
	UFUNCTION()
	void HandleButtonClicked();

	UFUNCTION()
	void OnButtonHover();

	UFUNCTION()
	void OnButtonUnhover();

	void RefreshVisuals();

	UPROPERTY()
	FMannequinTypes RowData;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> MyButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> MyImage = nullptr;
};
