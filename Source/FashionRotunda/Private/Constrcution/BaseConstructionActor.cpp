// Project by Rebel Art Studios.


#include "Constrcution/BaseConstructionActor.h"


// Sets default values
ABaseConstructionActor::ABaseConstructionActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent->SetMobility(EComponentMobility::Static);
}

void ABaseConstructionActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseConstructionActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}
