#pragma once

#include "BraintelligenceStatics.generated.h"

class UBraintelligenceAgent;
enum class EBraintelligenceEmotion : uint8;

UCLASS()
class UBraintelligenceStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Braintelligence", meta = (WorldContext = "WorldContextObject"))
	static void Initialize(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Braintelligence")
	static bool SendEvent(const FString& Event, const EBraintelligenceEmotion ExpectedEmotion);

	UFUNCTION(BlueprintCallable, Category = "Braintelligence")
	static void Shutdown();

protected:
	inline static UBraintelligenceAgent* Agent = nullptr;
};
