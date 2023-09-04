#include "BraintelligenceStatics.h"

#include "BraintelligenceAgent.h"
#include "BraintelligenceEmotion.h"

// ------------------------------------------------------------------------------------------------

void UBraintelligenceStatics::Initialize(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (IsValid(World))
	{
		Agent = NewObject<UBraintelligenceAgent>(World->GetGameInstance());
		Agent->Initialize();
	}
}

// ------------------------------------------------------------------------------------------------

bool UBraintelligenceStatics::SendEvent(const FString& Event, const EBraintelligenceEmotion ExpectedEmotion)
{
	if (IsValid(Agent))
	{
		return Agent->SendEvent(Event, ExpectedEmotion);
	}

	UE_LOG(LogTemp, Error, TEXT("Braintelligence not initialized!"));
	return false;
}

// ------------------------------------------------------------------------------------------------

void UBraintelligenceStatics::Shutdown()
{
	if (IsValid(Agent))
	{
		return Agent->Shutdown();
	}

	UE_LOG(LogTemp, Error, TEXT("Braintelligence not initialized!"));
}

// ------------------------------------------------------------------------------------------------
