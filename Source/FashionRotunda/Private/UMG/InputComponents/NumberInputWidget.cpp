// Project by Rebel Art Studios.

#include "UMG/InputComponents/NumberInputWidget.h"
#include "Components/EditableText.h"

void UNumberInputWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!InputTextBox) return;

	InputTextBox->OnTextCommitted.AddUniqueDynamic(this, &ThisClass::OnInputChange);
}

void UNumberInputWidget::OnInputChange(const FText& Input, ETextCommit::Type CommitType)
{
	if (CommitType == ETextCommit::Type::OnCleared) return;

	if (Input.IsNumeric())
	{
		CurrentInput = Input;
		OnNumberTextChanged.Broadcast(Input);
	}
	InputTextBox->SetText(CurrentInput);
}

void UNumberInputWidget::SetValue(const FText& Value)
{
	CurrentInput = Value;
	InputTextBox->SetText(CurrentInput);
}
