// Project by Rebel Art Studios.

#include "UMG/InputComponents/CheckboxInputWidget.h"
#include "Components/CheckBox.h"

void UCheckboxInputWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!InputCheckBox) return;

	InputCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &ThisClass::OnInputChange);
}

void UCheckboxInputWidget::OnInputChange(bool Input)
{
	CurrentInput = Input;
	OnCheckBoxValueChanged.Broadcast(Input);
}

void UCheckboxInputWidget::SetValue(bool Value)
{
	if (!InputCheckBox) return;
	CurrentInput = Value;
	InputCheckBox->SetCheckedState(Value ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
}
