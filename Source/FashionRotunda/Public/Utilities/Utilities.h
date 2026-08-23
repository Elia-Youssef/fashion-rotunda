// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utilities.generated.h"

// Light Params

class ABaseMannequinActor;

USTRUCT(BlueprintType)
struct FExposedLightParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool bEnabled = true;

	UPROPERTY(EditAnywhere)
	float LightIntensity = 5.0f;

	UPROPERTY(EditAnywhere)
	float LightTemperature = 6500.f;
};

USTRUCT(BlueprintType)
struct FHiddenLightParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool bCastShadow = true;

	UPROPERTY(EditAnywhere)
	float LightAttenuation = 500.f;

	UPROPERTY(EditAnywhere)
	float SpecularIntensity = 1.f;

	UPROPERTY(EditAnywhere)
	float VolumetricIntensity = 1.f;

	UPROPERTY(EditAnywhere)
	float IndirectIntensity = 1.f;

	UPROPERTY(EditAnywhere)
	FVector2D LightSize = FVector2D(50.f, 50.f);

	UPROPERTY(EditAnywhere)
	FVector2D BarnDoor = FVector2D(50.f, 50.f);
};

USTRUCT(BlueprintType)
struct FMannequinMaterial
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInstance> Material;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> Texture;

	UPROPERTY(EditAnywhere)
	FText Tooltip;
};

// Mannequins 
USTRUCT(BlueprintType)
struct FMannequinTypes : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName DressName = FName("Dress");

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> Thumbnail;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseMannequinActor> Actor;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> Audio;

	UPROPERTY(EditAnywhere)
	TArray<FMannequinMaterial> Materials;
};

// Studio Lights
USTRUCT(BlueprintType)
struct FStudioLights : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LightTag;
};
