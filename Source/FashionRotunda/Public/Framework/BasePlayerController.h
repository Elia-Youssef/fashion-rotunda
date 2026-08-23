// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UManagerWidget;
class ABaseCharacter;
class ABasePawn;

UCLASS()
class FASHIONROTUNDA_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Fade System
	UFUNCTION()
	void FadeIn();

	UFUNCTION()
	void FadeOut();

	// Pawn Switching 
	UFUNCTION()
	void RequestTogglePossession();

	UFUNCTION()
	void SwitchToPawn();

	UFUNCTION()
	void SwitchToCharacter();

	UFUNCTION()
	void AllowMovement();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnFadeInFinished();

	UFUNCTION()
	void OnFadeOutFinished();

	ABasePawn* SpawnBasePawn(const FTransform& Transform);

	ABaseCharacter* SpawnCharacter(const FTransform& Transform);

	// Possession Helpers
	void PossessPawn(APawn* NewPawn);

	void RestoreControlRotation(APawn* To);

	void BlendToPawn(APawn* InPawn);

	// Configurations
	UPROPERTY(EditDefaultsOnly)
	bool bSpawnIfMissing = true;

	UPROPERTY(EditDefaultsOnly)
	bool bBlendCamera = true;

	UPROPERTY(EditDefaultsOnly)
	float BlendTime = 0.25f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABasePawn> PawnClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseCharacter> CharacterClass;

	UPROPERTY(Transient)
	TObjectPtr<ABasePawn> BasePawnInstance = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<ABaseCharacter> CharacterInstance = nullptr;

	FTransform LastCharacterTransform = FTransform::Identity;
	FTransform LastPawnTransform = FTransform::Identity;

	// Widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UManagerWidget> ManagerWidgetClass = nullptr;

	UPROPERTY()
	TObjectPtr<UManagerWidget> ManagerWidget = nullptr;
};
