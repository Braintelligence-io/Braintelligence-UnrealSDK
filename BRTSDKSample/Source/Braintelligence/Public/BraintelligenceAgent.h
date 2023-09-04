#pragma once

#include "Interfaces/IHttpRequest.h"
#include "IWebSocket.h"
#include "BraintelligenceAgent.generated.h"

enum class EBraintelligenceEmotion : uint8;

UCLASS(Blueprintable)
class UBraintelligenceAgent : public UObject
{
	GENERATED_BODY()

public:
	void Initialize();
	void GetLocalServerAddress(const FString& Key);
	void OnHttpRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void ConnectWebSocket(const FString& Address);
	bool IsConnected() const;
	void TakeInGameScreenshot();
	void AcceptScreenshot(int32 InSizeX, int32 InSizeY, const TArray<FColor>& InImageData) const;
	FString GetKey() const;
	void Shutdown() const;
	bool SendEvent(const FString& Event, const EBraintelligenceEmotion ExpectedEmotion) const;
	bool SendBuffer(const void* Data, int32 Size) const;

	TSharedPtr<IWebSocket> WebSocket;
	FTimerHandle TimerHandler;
};
