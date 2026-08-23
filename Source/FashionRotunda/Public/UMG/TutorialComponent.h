// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialComponent.generated.h"

class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseButtonClicked);

UCLASS()
class FASHIONROTUNDA_API UTutorialComponent : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY()
	FOnCloseButtonClicked OnCloseButtonClicked;
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void OnFadeFinished();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FadeAnimation;
};
