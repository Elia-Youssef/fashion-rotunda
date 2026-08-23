// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CheckboxInputWidget.generated.h"

class UCheckBox;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCheckBoxValueChanged, bool, Value);

UCLASS()
class FASHIONROTUNDA_API UCheckboxInputWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox> InputCheckBox;

	bool CurrentInput;

public:
	FOnCheckBoxValueChanged OnCheckBoxValueChanged;

	void SetValue(bool Value);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnInputChange(bool Input);
};
