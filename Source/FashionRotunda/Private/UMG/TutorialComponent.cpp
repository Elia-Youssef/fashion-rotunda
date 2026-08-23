// Project by Rebel Art Studios.


#include "UMG/TutorialComponent.h"
#include "Components/Button.h"

void UTutorialComponent::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.RemoveAll(this);
		CloseButton->OnClicked.AddDynamic(this, &UTutorialComponent::OnButtonClicked);
	}

	if (FadeAnimation)
	{
		FWidgetAnimationDynamicEvent DynamicEvent;
		DynamicEvent.BindUFunction(this, "OnFadeFinished");
		BindToAnimationFinished(FadeAnimation, DynamicEvent);
	}
}

void UTutorialComponent::OnButtonClicked()
{
	if (FadeAnimation)
	{
		PlayAnimationForward(FadeAnimation);
	}
}

void UTutorialComponent::OnFadeFinished()
{
	SetVisibility(ESlateVisibility::Collapsed);
	OnCloseButtonClicked.Broadcast();
}
