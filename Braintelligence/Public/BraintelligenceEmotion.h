#pragma once

#include "CoreMinimal.h"
#include "BraintelligenceEmotion.generated.h"

UENUM(BlueprintType)
enum class EBraintelligenceEmotion : uint8
{
	None,
	Engagement,
	Frustration,
	Boredom,
	Relaxed,
};
