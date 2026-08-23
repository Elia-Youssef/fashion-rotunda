// Project by Rebel Art Studios.


#include "Framework/BasePlayerController.h"
#include "Framework/BaseCharacter.h"
#include "Framework/BasePawn.h"
#include "MannequinSystem/MannequinSubsystem.h"
#include "UMG/ManagerWidget.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Force Fade
	if (PlayerCameraManager)
	{
		PlayerCameraManager->SetManualCameraFade(1.f, FLinearColor::Black, true);
	}

	// Create HUD
	if (ManagerWidgetClass && !ManagerWidget)
	{
		ManagerWidget = CreateWidget<UManagerWidget>(this, ManagerWidgetClass);
		if (ManagerWidget)
		{
			ManagerWidget->AddToViewport();
			FInputModeGameAndUI Input;
			SetInputMode(Input);
		}
	}

	// Caching At Begin Play
	if (APawn* MyPawn = GetPawn())
	{
		if (ABaseCharacter* C = Cast<ABaseCharacter>(MyPawn))
		{
			CharacterInstance = C;
			LastCharacterTransform = C->GetActorTransform();
		}
		else if (ABasePawn* P = Cast<ABasePawn>(MyPawn))
		{
			BasePawnInstance = P;
			LastPawnTransform = P->GetActorTransform();
		}
	}

	FTimerHandle FadeTimerHandle;
	GetWorldTimerManager().SetTimer(FadeTimerHandle, this,
	                                &ABasePlayerController::FadeIn, 1.f, false);
}

void ABasePlayerController::FadeIn()
{
	if (PlayerCameraManager)
	{
		PlayerCameraManager->StartCameraFade(1.f, 0.f, 1.f, FLinearColor::Black, true);

		FTimerHandle FadeTimerHandle;
		GetWorldTimerManager().SetTimer(FadeTimerHandle, this, &ABasePlayerController::OnFadeInFinished, 1.f, false);
	}
}

void ABasePlayerController::FadeOut()
{
	if (PlayerCameraManager)
	{
		PlayerCameraManager->StartCameraFade(0.f, 1.f, 1.f, FLinearColor::Black, true);

		FTimerHandle FadeTimerHandle;
		GetWorldTimerManager().SetTimer(FadeTimerHandle, this, &ABasePlayerController::OnFadeOutFinished, 0.5f, false);
	}
}

void ABasePlayerController::OnFadeInFinished()
{
	if (ManagerWidget)
	{
		ManagerWidget->SpawnDespawnWidget();
	}
	bShowMouseCursor = true;
}

void ABasePlayerController::OnFadeOutFinished()
{
}

void ABasePlayerController::AllowMovement()
{
	if (ABasePawn* MyPawn = Cast<ABasePawn>(GetPawn()))
	{
		MyPawn->bAllowInput = true;
	}
	else if (ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(GetPawn()))
	{
		MyCharacter->bAllowInput = true;
	}
}

void ABasePlayerController::RequestTogglePossession()
{
	if (ABasePawn* BasePawn = Cast<ABasePawn>(GetPawn()))
	{
		LastPawnTransform = BasePawn->GetActorTransform();
		LastPawnTransform.SetRotation(GetControlRotation().Quaternion());
		SwitchToCharacter();
	}
	else if (ABaseCharacter* BaseChar = Cast<ABaseCharacter>(GetPawn()))
	{
		LastCharacterTransform = BaseChar->GetActorTransform();
		LastCharacterTransform.SetRotation(GetControlRotation().Quaternion());
		SwitchToPawn();
	}
}

void ABasePlayerController::SwitchToPawn()
{
	if (!BasePawnInstance || !IsValid(BasePawnInstance))
	{
		LastPawnTransform = FTransform{
			FRotator{-15, 90, 0},
			FVector{0.f, 0.f, 150.f}
		};
		BasePawnInstance = SpawnBasePawn(LastPawnTransform);
	}
	else
	{
		BasePawnInstance->SetActorTransform(LastPawnTransform);
	}

	BlendToPawn(BasePawnInstance);
}

void ABasePlayerController::SwitchToCharacter()
{
	if (!CharacterInstance || !IsValid(CharacterInstance))
	{
		CharacterInstance = SpawnCharacter(LastCharacterTransform);
	}
	else
	{
		CharacterInstance->SetActorTransform(LastCharacterTransform);
	}

	BlendToPawn(CharacterInstance);
}

void ABasePlayerController::BlendToPawn(APawn* InPawn)
{
	if (!IsValid(InPawn)) return;

	if (bBlendCamera && BlendTime >= 0.01)
	{
		FViewTargetTransitionParams Params;
		Params.BlendTime = BlendTime;
		SetViewTarget(InPawn, Params);

		FTimerHandle TempHandle;
		GetWorldTimerManager().SetTimer(TempHandle, [this, InPawn]()
		{
			PossessPawn(InPawn);
		}, BlendTime, false);
	}
	else
	{
		PossessPawn(InPawn);
	}
}

ABasePawn* ABasePlayerController::SpawnBasePawn(const FTransform& Transform)
{
	if (!PawnClass) return nullptr;

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetPawn();
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	return GetWorld()->SpawnActor<ABasePawn>(PawnClass, Transform, Params);
}

ABaseCharacter* ABasePlayerController::SpawnCharacter(const FTransform& Transform)
{
	if (!CharacterClass) return nullptr;

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetPawn();
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	return GetWorld()->SpawnActor<ABaseCharacter>(CharacterClass, Transform, Params);
}

void ABasePlayerController::PossessPawn(APawn* NewPawn)
{
	if (!IsValid(NewPawn)) return;

	if (APawn* Old = GetPawn())
	{
		Old->SetActorEnableCollision(false);
		Old->SetActorHiddenInGame(true);
	}

	UnPossess();
	Possess(NewPawn);

	NewPawn->SetActorEnableCollision(true);
	NewPawn->SetActorHiddenInGame(false);

	AllowMovement();
}

void ABasePlayerController::RestoreControlRotation(APawn* To)
{
	FRotator NewActorRotation = To->GetActorRotation();

	NewActorRotation.Yaw = ControlRotation.Yaw;
	To->SetActorRotation(NewActorRotation);

	SetControlRotation(ControlRotation);
}
