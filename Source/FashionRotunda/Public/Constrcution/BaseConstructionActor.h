// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseConstructionActor.generated.h"

UCLASS()
class FASHIONROTUNDA_API ABaseConstructionActor : public AActor
{
	GENERATED_BODY()

public:
	ABaseConstructionActor();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	
};
