// Project by Rebel Art Studios.


#include "MannequinSystem/MannequinSubsystem.h"

#include "Components/DirectionalLightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Framework/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Lighting/BaseLightActor.h"
#include "MannequinSystem/BaseMannequinActor.h"
#include "Utilities/Utilities.h"


void UMannequinSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle, this, &UMannequinSubsystem::RegisterInitialActor, 0.5f, false);
	}
}

void UMannequinSubsystem::RegisterInitialActor()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseMannequinActor::StaticClass(), FoundActors);
	if (FoundActors.IsEmpty()) return;

	if (ABaseMannequinActor* FoundActor = Cast<ABaseMannequinActor>(FoundActors[0]))
	{
		CurrentMannequin = FoundActor;
	}
}

void UMannequinSubsystem::SpawnItem(FMannequinTypes& Type)
{
	if (!GetWorld() || !Type.Actor) return;

	CurrentRow = Type;

	// Destroy Old Actor If Any
	if (ABaseMannequinActor* Old = CurrentMannequin.Get())
	{
		if (!Old->IsActorBeingDestroyed())
		{
			Old->Destroy();
		}
		CurrentMannequin.Reset();
	}

	// Spawn New Actor From Row Data
	const FVector Location = FVector::ZeroVector;
	const FRotator Rotation = FRotator(0.f, -90.f, 0.f);
	const FVector Scale = FVector(1.f, 1.f, 1.f);
	const FTransform Transform = FTransform(Rotation, Location, Scale);

	ABaseMannequinActor* NewActor = GetWorld()->SpawnActorDeferred<ABaseMannequinActor>(Type.Actor, Transform);
	if (!IsValid(NewActor)) return;

	NewActor->FinishSpawning(Transform);
	CurrentMannequin = NewActor;
}

void UMannequinSubsystem::RotateActor()
{
	if (ABaseMannequinActor* Current = CurrentMannequin.Get())
	{
		Current->ToggleRotation();
	}
}

void UMannequinSubsystem::ResetActorRotation()
{
	if (ABaseMannequinActor* Current = CurrentMannequin.Get())
	{
		Current->ResetRotation();
	}
}

void UMannequinSubsystem::AllowPlayerMovement()
{
	if (!GetWorld()) return;
	if (ABasePlayerController* PC = GetWorld()->GetFirstPlayerController<ABasePlayerController>())
	{
		PC->AllowMovement();
	}
}

void UMannequinSubsystem::SwitchPawnType()
{
	UWorld* World = GetWorld();
	if (!World) return;

	ABasePlayerController* PC = World->GetFirstPlayerController<ABasePlayerController>();
	if (!PC) return;

	PC->RequestTogglePossession();
}

void UMannequinSubsystem::CacheStudioLights(const TArray<FName>& Tags)
{
	for (const FName& Tag : Tags)
	{
		FCachedLightActors Actors;

		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ABaseLightActor::StaticClass(), Tag, OutActors);

		for (AActor* Actor : OutActors)
		{
			if (ABaseLightActor* LightActor = Cast<ABaseLightActor>(Actor); IsValid(LightActor))
			{
				Actors.Lights.AddUnique(LightActor);
			}
		}
		StudioLights.Add(Tag, Actors);
	}
}

FExposedLightParams UMannequinSubsystem::GetStudioLightData(const FName& Tag)
{
	FCachedLightActors* Actors = StudioLights.Find(Tag);
	if (!Actors || Actors->Lights.IsEmpty()) return FExposedLightParams{};

	ABaseLightActor* LightActor = Actors->Lights[0];
	if (!IsValid(LightActor)) return FExposedLightParams{};

	return LightActor->GetLightData();
}

void UMannequinSubsystem::SetStudioLightData(const FName& Tag, const FExposedLightParams& LightParams)
{
	FCachedLightActors* Actors = StudioLights.Find(Tag);
	if (!Actors) return;

	for (ABaseLightActor* Actor : Actors->Lights)
	{
		if (!IsValid(Actor)) return;
		Actor->SetLightData(LightParams);
	}
}

void UMannequinSubsystem::SetSunIntensity(float Value)
{
	if (!IsValid(DirectionalLightComp)) return;
	DirectionalLightComp->SetIntensity(Value);
}

float UMannequinSubsystem::GetSunIntensity()
{
	SetDirectionalLight();
	if (!IsValid(DirectionalLightComp)) return 0.f;
	return DirectionalLightComp->Intensity;
}

void UMannequinSubsystem::SetSunPitch(float Value)
{
	if (!IsValid(DirectionalLight)) return;
	InitialLightRotation.Pitch = Value;
	DirectionalLight->SetActorRotation(InitialLightRotation);
}

float UMannequinSubsystem::GetSunPitch()
{
	SetDirectionalLight();
	if (!IsValid(DirectionalLight)) return 0.f;
	return DirectionalLight->GetActorRotation().Pitch;
}

void UMannequinSubsystem::SetMannequinMaterial(UMaterialInstance* Material)
{
	ABaseMannequinActor* Mann = CurrentMannequin.Get();
	if (!IsValid(Mann)) return;

	TArray<UActorComponent*> Comps = Mann->GetComponentsByTag(UStaticMeshComponent::StaticClass(),
	                                                          FName("MaterialControl"));
	for (UActorComponent* Comp : Comps)
	{
		if (UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(Comp))
		{
			MeshComp->SetMaterial(0, Material);
		}
	}
}

void UMannequinSubsystem::SetDirectionalLight()
{
	if (!IsValid(DirectionalLight))
	{
		AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ADirectionalLight::StaticClass());
		DirectionalLight = Cast<ADirectionalLight>(Actor);

		if (IsValid(DirectionalLight))
		{
			InitialLightRotation = DirectionalLight->GetActorRotation();
		}
	}

	if (!IsValid(DirectionalLight))
	{
		DirectionalLightComp = nullptr;
		return;
	}

	if (!IsValid(DirectionalLightComp))
	{
		UActorComponent* Comp = DirectionalLight->GetComponentByClass(UDirectionalLightComponent::StaticClass());
		DirectionalLightComp = Cast<UDirectionalLightComponent>(Comp);
	}
}
