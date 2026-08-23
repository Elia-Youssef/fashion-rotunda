// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "MaterialSelectorWidget.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/Utilities.h"
#include "MannequinInfoContainer.generated.h"

class UHorizontalBox;
class UMultiLineEditableText;
class UButton;
class UTextBlock;
class UImage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRotateSelected);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetRotationSelected);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioSelected, const FMannequinTypes&, Type);

UCLASS()
class FASHIONROTUNDA_API UMannequinInfoContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void PopulateInfo(const FMannequinTypes& Types);

	// Delegates
	UPROPERTY()
	FOnRotateSelected OnRotateSelected;

	UPROPERTY(BlueprintAssignable)
	FOnResetRotationSelected OnResetRotationSelected;

	UPROPERTY(BlueprintAssignable)
	FOnAudioSelected OnAudioSelected;

	FOnMaterialSelected OnMaterialSelected;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void RotateButtonPressed();

	UFUNCTION()
	void ResetRotationButtonPressed();

	UFUNCTION()
	void AudioButtonPressed();

	UFUNCTION()
	void MaterialButtonPressed();
	
	UFUNCTION()
	void OnMaterialSelectorClicked(UMaterialInstance* Material);

private:
	UPROPERTY()
	FMannequinTypes CurrentType;

	// Components
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> DressImage = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DressName = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UMultiLineEditableText> DressInfo = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> RotateButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ResetButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> AudioButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> MaterialButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UHorizontalBox> MaterialsContainer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMaterialSelectorWidget> MaterialSelectorClass;
};
