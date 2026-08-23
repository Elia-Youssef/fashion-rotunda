// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utilities/Utilities.h"
#include "ManagerWidget.generated.h"


class UOverlay;
class UCanvasPanel;
class UHorizontalBox;
class UButton;
class ULightContainerWidget;
class UTutorialComponent;
class UMannequinInfoContainer;
class UMannequinTypesContainer;
class UVerticalBox;
class UMannequinSubsystem;

UCLASS()
class FASHIONROTUNDA_API UManagerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SpawnDespawnWidget();

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleMannequinTypeSelected(FMannequinTypes Selected);

	UFUNCTION()
	void HandleRotateActorSelected();

	UFUNCTION()
	void HandleResetActorRotationSelected();

	UFUNCTION()
	void HandleAudioSelected(FMannequinTypes Selected);

	UFUNCTION()
	void HandlePawnTypeChanged();

	UFUNCTION()
	void ShowComponents();

	UFUNCTION()
	void OnStudioLightsButtonClicked();

	UFUNCTION()
	void OnMaterialSelected(UMaterialInstance* Material);

private:
	// ======== ANIMATION ========

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> RootAnimation;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FadeAnimation;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> InfoContainerAnim;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> StudioLightsContainerAnim;

	// ======== WIDGETS ========

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> RootContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> BaseContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SwitchPawnButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMannequinTypesContainer> MannequinTypesContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMannequinInfoContainer> InfoContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTutorialComponent> TutorialComponent;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StudioLightsButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<ULightContainerWidget> StudioLightsContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> LightsHB;

	// ======== SUBSYSTEM ========

	UPROPERTY()
	TObjectPtr<UMannequinSubsystem> Subsystem;
};
