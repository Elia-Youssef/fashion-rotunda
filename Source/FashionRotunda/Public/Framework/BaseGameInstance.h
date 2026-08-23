// Project by Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FASHIONROTUNDA_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta= (KeyName = "CVar Name", ValueName = "CVar Value"))
	TMap<FName, FString> CVars;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1", ClampMax = "4"))
	int32 OverallScalabilityValue = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	float MaxFPS = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	FIntPoint ScreenSize = FIntPoint(1920, 1080);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TexturePoolSize = 6000;

	UFUNCTION(BlueprintCallable)
	void ApplySettings();

	//Testing These Now // Will Not Use
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StreamingBoost = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFullyLoadUsedTextures = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bNaniteFallbackMesh = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NaniteStreamingNumPrims = 0;
};
