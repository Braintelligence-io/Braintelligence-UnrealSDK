#pragma once
#include "BraintelligenceSettings.generated.h"

UCLASS(config = BraintelligenceSettings)
class UBraintelligenceSettings : public UObject
{
	GENERATED_BODY()

public:
	UBraintelligenceSettings(const FObjectInitializer& OBJ);

	UPROPERTY(Config, EditAnywhere, Category = "Braintelligence")
	FString Key;
};
