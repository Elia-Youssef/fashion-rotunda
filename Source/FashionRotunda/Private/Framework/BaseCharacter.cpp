// Project by Rebel Art Studios.


#include "Framework/BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Framework/BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	MovementComponent = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	MovementComponent->MaxWalkSpeed = 300.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	Camera->bUsePawnControlRotation = true;
	Camera->SetFieldOfView(80.f);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
	if (ABasePlayerController* PC = Cast<ABasePlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(IA_LookAround, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);
		EIC->BindAction(IA_MoveAround, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);
		EIC->BindAction(IA_SwitchPawn, ETriggerEvent::Triggered, this, &ABaseCharacter::SwitchPawn);
	}
}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	if (!bAllowInput) return;

	const FVector2D MoveValue = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MoveValue.Y, true);
	AddMovementInput(GetActorRightVector(), MoveValue.X, true);
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	if (!bAllowInput) return;

	const FVector2D LookValue = Value.Get<FVector2D>();
	AddControllerYawInput(LookValue.X);
	AddControllerPitchInput(LookValue.Y);
}

void ABaseCharacter::SwitchPawn()
{
	if (ABasePlayerController* PC = Cast<ABasePlayerController>(GetController()))
		PC->RequestTogglePossession();
}
