// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/Utilities.h"
#include "MaterialSelectorWidget.generated.h"

class UToolTipWidget;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaterialSelected, UMaterialInstance*, Material);

class UButton;
class UImage;
/**
 * 
 */
UCLASS()
class FASHIONROTUNDA_API UMaterialSelectorWidget : public UUserWidget
{
	GENERATED_BODY()

	FMannequinMaterial Data;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UToolTipWidget> CustomTooltip;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image;

	UFUNCTION()
	void OnButtonClick();

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnhovered();

public:
	void SetValue(const FMannequinMaterial& Material);

	FOnMaterialSelected OnMaterialSelected;
};
