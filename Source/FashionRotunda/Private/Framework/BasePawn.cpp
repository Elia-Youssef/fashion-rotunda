// Project by Rebel Art Studios.


#include "Framework/BasePawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Framework/BasePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = InitialSpringArmLength;
	SpringArm->bUsePawnControlRotation = true;

	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 10.f;
	SpringArm->CameraRotationLagSpeed = 10.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->SetFieldOfView(75.f);
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePawn::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
	if (ABasePlayerController* PC = Cast<ABasePlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(IMC, 0);
		}
	}
}

void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(IA_Orbit, ETriggerEvent::Triggered, this, &ABasePawn::Orbit);
		EIC->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &ABasePawn::Zoom);
		EIC->BindAction(IA_Pan, ETriggerEvent::Triggered, this, &ABasePawn::Pan);
		EIC->BindAction(IA_SwitchPawn, ETriggerEvent::Triggered, this, &ABasePawn::SwitchPawn);

		EIC->BindAction(RightClickAction, ETriggerEvent::Started, this, &ABasePawn::OnRightClickStarted);
		EIC->BindAction(RightClickAction, ETriggerEvent::Completed, this, &ABasePawn::OnRightClickCompleted);
	}
}

void ABasePawn::Orbit(const FInputActionValue& Value)
{
	if (!bAllowInput || !SpringArm) return;

	if (bRightClickDown)
	{
		Pan(Value);
	}
	else
	{
		const FVector2D OrbitValue = Value.Get<FVector2D>();
		AddControllerYawInput(OrbitValue.X);
		AddControllerPitchInput(OrbitValue.Y);
	}
}

void ABasePawn::Zoom(const FInputActionValue& Value)
{
	if (!bAllowInput || !SpringArm) return;

	const float Direction = Value.Get<float>();
	const float NewArmLength = FMath::Clamp(
		Direction * StepSize + CurrentSpringArmLength, SpringArmRange.X, SpringArmRange.Y);

	SpringArm->TargetArmLength = NewArmLength;
	CurrentSpringArmLength = NewArmLength;
}

void ABasePawn::Pan(const FInputActionValue& Value)
{
	if (!bAllowInput) return;
	const FVector2D PanValue = Value.Get<FVector2D>();
	if (PanValue.IsNearlyZero()) return;

	const float DeltaTime = GetWorld()->GetDeltaSeconds();

	const FVector WorldUp = FVector(0.f, 0.f, -1.f);
	const FVector DeltaOffset = WorldUp * PanValue.Y * PanSpeed * DeltaTime;

	FVector NewLocation = GetActorLocation() + DeltaOffset;
	NewLocation.Z = FMath::Clamp(NewLocation.Z, 10.f, 500.f);

	SetActorLocation(NewLocation, true);
}

void ABasePawn::SwitchPawn()
{
	if (ABasePlayerController* PC = Cast<ABasePlayerController>(GetController()))
		PC->RequestTogglePossession();
}

void ABasePawn::OnRightClickStarted(const FInputActionValue& Value)
{
	bRightClickDown = true;
}

void ABasePawn::OnRightClickCompleted(const FInputActionValue& Value)
{
	bRightClickDown = false;
}
