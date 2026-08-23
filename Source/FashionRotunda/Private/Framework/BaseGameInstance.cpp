// Project by Rebel Art Studios.


#include "Framework/BaseGameInstance.h"
#include "GameFramework/GameUserSettings.h"
#include "HAL/IConsoleManager.h"

void UBaseGameInstance::Init()
{
	Super::Init();
	ApplySettings();
}

void UBaseGameInstance::ApplySettings()
{
	if (UGameUserSettings* GS = GEngine->GetGameUserSettings())
	{
		GS->SetScreenResolution(ScreenSize);
		GS->SetFrameRateLimit(MaxFPS);
		GS->SetOverallScalabilityLevel(OverallScalabilityValue);
		GS->ApplySettings(false);
		GS->SaveSettings();

		// Console Variables
		if (IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("r.Streaming.PoolSize")))
		{
			CVar->Set(TexturePoolSize, ECVF_SetByGameSetting);
			UE_LOG(LogTemp, Warning, TEXT("Applied Texture Pool Size: %d MB"), TexturePoolSize);
		}

		for (const auto& CVarEntry : CVars)
		{
			const FString CVarName = CVarEntry.Key.ToString();
			const FString& Value = CVarEntry.Value;

			if (IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(*CVarName))
			{
				// Force the value in code
				CVar->Set(*Value, ECVF_SetByGameSetting);
				UE_LOG(LogTemp, Warning, TEXT("Applied CVar: %s = %s"), *CVarName, *Value);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("CVar not found: %s"), *CVarName);
			}
		}
	}
}
