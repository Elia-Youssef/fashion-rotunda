// Project by Rebel Art Studios.


#include "UMG/ManagerWidget.h"

#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Overlay.h"
#include "MannequinSystem/MannequinSubsystem.h"
#include "UMG/MannequinInfoContainer.h"
#include "UMG/MannequinTypesContainer.h"
#include "UMG/TutorialComponent.h"
#include "UMG/LightingComponents/LightContainerWidget.h"

void UManagerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (const UGameInstance* GI = GetGameInstance())
	{
		Subsystem = GI->GetSubsystem<UMannequinSubsystem>();
	}

	if (RootContainer)
	{
		RootContainer->SetRenderOpacity(0.f);
	}

	if (BaseContainer)
	{
		BaseContainer->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (SwitchPawnButton)
	{
		SwitchPawnButton->OnClicked.AddUniqueDynamic(this, &UManagerWidget::HandlePawnTypeChanged);
	}

	if (MannequinTypesContainer)
	{
		MannequinTypesContainer->OnTypeSelected.AddUniqueDynamic(this, &UManagerWidget::HandleMannequinTypeSelected);
	}

	if (InfoContainer)
	{
		InfoContainer->OnRotateSelected.AddUniqueDynamic(this, &UManagerWidget::HandleRotateActorSelected);
		InfoContainer->OnResetRotationSelected.AddUniqueDynamic(this, &UManagerWidget::HandleResetActorRotationSelected);
		InfoContainer->OnMaterialSelected.AddUniqueDynamic(this, &ThisClass::OnMaterialSelected);
		InfoContainer->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (TutorialComponent)
	{
		TutorialComponent->OnCloseButtonClicked.AddUniqueDynamic(this, &UManagerWidget::ShowComponents);
	}

	if (StudioLightsButton)
	{
		StudioLightsButton->OnClicked.AddUniqueDynamic(this, &UManagerWidget::OnStudioLightsButtonClicked);
	}

	if (StudioLightsContainer)
	{
		StudioLightsContainer->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UManagerWidget::SpawnDespawnWidget()
{
	if (RootAnimation)
	{
		PlayAnimationForward(RootAnimation);
	}
}

void UManagerWidget::HandleMannequinTypeSelected(FMannequinTypes Selected)
{
	if (Subsystem)
	{
		Subsystem->SpawnItem(Selected);
	}

	if (InfoContainer)
	{
		InfoContainer->PopulateInfo(Selected);
		if (InfoContainer->GetVisibility() == ESlateVisibility::Collapsed)
		{
			PlayAnimationForward(InfoContainerAnim);
		}
	}
}

void UManagerWidget::HandleRotateActorSelected()
{
	Subsystem->RotateActor();
}

void UManagerWidget::HandleResetActorRotationSelected()
{
	Subsystem->ResetActorRotation();
}

void UManagerWidget::HandleAudioSelected(FMannequinTypes Selected)
{
}

void UManagerWidget::HandlePawnTypeChanged()
{
	Subsystem->SwitchPawnType();
}

void UManagerWidget::ShowComponents()
{
	if (FadeAnimation)
	{
		PlayAnimationForward(FadeAnimation);
	}
	if (Subsystem)
	{
		Subsystem->AllowPlayerMovement();
	}
}

void UManagerWidget::OnStudioLightsButtonClicked()
{
	if (!StudioLightsContainerAnim) return;

	if (StudioLightsContainer->GetVisibility() == ESlateVisibility::Collapsed)
	{
		PlayAnimationForward(StudioLightsContainerAnim);
	}
	else
	{
		PlayAnimationReverse(StudioLightsContainerAnim);
	}
}

void UManagerWidget::OnMaterialSelected(UMaterialInstance* Material)
{
	if (!Subsystem) return;
	Subsystem->SetMannequinMaterial(Material);
}
