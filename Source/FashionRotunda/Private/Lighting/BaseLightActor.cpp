// Project by Rebel Art Studios.


#include "Lighting/BaseLightActor.h"

#include "Components/LocalLightComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/RectLightComponent.h"

ABaseLightActor::ABaseLightActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent->SetMobility(EComponentMobility::Static);
}

void ABaseLightActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseLightActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	RegisterLight();
	ControlLight();
}

void ABaseLightActor::RegisterLight()
{
	if (IsValid(MyLight)) return;

	TInlineComponentArray<ULocalLightComponent*> Lights(this);
	if (Lights.Num() > 0) MyLight = Lights[0];

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Registered light component");
}

void ABaseLightActor::ControlLight()
{
	if (!IsValid(MyLight)) return;

	MyLight->SetVisibility(ExposedLightParams.bEnabled);
	MyLight->SetIntensityUnits(ELightUnits::Candelas);
	MyLight->SetUseTemperature(true);
	MyLight->SetIntensity(ExposedLightParams.LightIntensity);
	MyLight->SetTemperature(ExposedLightParams.LightTemperature);

	MyLight->SetCastShadows(HiddenLightParams.bCastShadow);
	MyLight->SetAttenuationRadius(HiddenLightParams.LightAttenuation);
	MyLight->SetSpecularScale(HiddenLightParams.SpecularIntensity);
	MyLight->SetVolumetricScatteringIntensity(HiddenLightParams.VolumetricIntensity);
	MyLight->SetIndirectLightingIntensity(HiddenLightParams.IndirectIntensity);

	if (URectLightComponent* RectLight = Cast<URectLightComponent>(MyLight))
	{
		RectLight->SetSourceWidth(HiddenLightParams.LightSize.X);
		RectLight->SetSourceHeight(HiddenLightParams.LightSize.Y);
		RectLight->SetBarnDoorLength(HiddenLightParams.BarnDoor.X);
		RectLight->SetBarnDoorAngle(HiddenLightParams.BarnDoor.Y);
	}

	else if (UPointLightComponent* PointLight = Cast<UPointLightComponent>(MyLight))
	{
		PointLight->SetSourceLength(HiddenLightParams.LightSize.X);
		PointLight->SetSourceRadius(HiddenLightParams.LightSize.Y);
	}
}

void ABaseLightActor::SetLightData(const FExposedLightParams& Data)
{
	ExposedLightParams = Data;
	ControlLight();
}
