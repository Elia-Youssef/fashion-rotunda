// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NumberInputWidget.generated.h"

class UEditableText;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNumberTextChanged, const FText&, Text);

UCLASS()
class FASHIONROTUNDA_API UNumberInputWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableText> InputTextBox;

	FText CurrentInput;

public:
	FOnNumberTextChanged OnNumberTextChanged;

	void SetValue(const FText& Value);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnInputChange(const FText& Input, ETextCommit::Type CommitType);
};
