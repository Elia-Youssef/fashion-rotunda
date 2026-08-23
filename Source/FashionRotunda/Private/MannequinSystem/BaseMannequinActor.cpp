// Project by Rebel Art Studios.


#include "MannequinSystem/BaseMannequinActor.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ABaseMannequinActor::ABaseMannequinActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent->SetMobility(EComponentMobility::Movable);

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Sphere"));
	CapsuleCollision->SetupAttachment(RootComponent);
	CapsuleCollision->SetMobility(EComponentMobility::Movable);
	CapsuleCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	CapsuleCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	CapsuleCollision->SetRelativeLocation(FVector(0, 0, 100.f));
	CapsuleCollision->SetCapsuleHalfHeight(180.f);
	CapsuleCollision->SetCapsuleRadius(80.f);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->SetupAttachment(RootComponent);
	ArrowComponent->SetRelativeLocation(FVector(50, 0, 50.f));
}

void ABaseMannequinActor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetActorRotation().Yaw;
}


void ABaseMannequinActor::ToggleRotation()
{
	if (bIsRotating) PauseRotation();
	else StartRotation();
}

void ABaseMannequinActor::StartRotation()
{
	if (GetWorldTimerManager().IsTimerPaused(RotationTimer))
	{
		GetWorldTimerManager().UnPauseTimer(RotationTimer);
	}
	else if (!GetWorldTimerManager().IsTimerActive(RotationTimer))
	{
		GetWorldTimerManager().SetTimer(RotationTimer, this, &ThisClass::Rotate, RotationInterval, true);
	}
	bIsRotating = true;
}

void ABaseMannequinActor::PauseRotation()
{
	if (GetWorldTimerManager().IsTimerActive(RotationTimer))
	{
		GetWorldTimerManager().PauseTimer(RotationTimer);
		bIsRotating = false;
		bShouldStop = false;
		RotationDirection = 1.f;
	}
}

void ABaseMannequinActor::ResetRotation()
{
	CurrentYaw = FMath::Abs(GetActorRotation().Yaw - InitialYaw);
	if (FMath::IsNearlyEqual(CurrentYaw, 0.f, 1.f)) return;

	const bool bPrevShouldStop = bShouldStop;
	bShouldStop = true;

	if (CurrentYaw < 180.f)
	{
		RotationDirection = -1.f;
	}
	if (!bIsRotating)
	{
		StartRotation();
	}
	else if (bPrevShouldStop)
	{
		ToggleRotation();
	}
}

void ABaseMannequinActor::Rotate()
{
	float Yaw = GetActorRotation().Yaw;
	const float AddedRotation = (360.f / TotalRotationTime) * RotationDirection * RotationInterval;

	Yaw += AddedRotation;
	Yaw = FRotator::NormalizeAxis(Yaw);

	SetActorRotation(FRotator(GetActorRotation().Pitch, Yaw, GetActorRotation().Roll));

	if (bShouldStop && FMath::IsNearlyEqual(GetActorRotation().Yaw, InitialYaw, 1.f))
	{
		SetActorRotation(FRotator(GetActorRotation().Pitch, InitialYaw, GetActorRotation().Roll));
		bShouldStop = false;
		bIsRotating = false;
		GetWorldTimerManager().ClearTimer(RotationTimer);
		RotationDirection = 1.f;
	}
}
