#include "BraintelligenceAgent.h"

#include "BraintelligenceEmotion.h"
#include "BraintelligenceSettings.h"
#include "HttpModule.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "WebSocketsModule.h"
#include "Interfaces/IHttpResponse.h"

// ------------------------------------------------------------------------------------------------

void UBraintelligenceAgent::Initialize()
{
	const FString Key = GetKey();
	if (Key.IsEmpty())
	{
		UE_LOG(LogTemp, Error,
		       TEXT("Please add Braintelligence-Key in the project's settings Braintelligence section!"));
		return;
	}

	GetLocalServerAddress(Key);
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &UBraintelligenceAgent::TakeInGameScreenshot, 1.0f, true,
	                                       0.0f);
}

// ------------------------------------------------------------------------------------------------

void UBraintelligenceAgent::GetLocalServerAddress(const FString& Key)
{
	const FString URL = "https://braintelligence.io/api/localsynchronizer/" + Key;

	// Create a new HTTP request object
	const TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UBraintelligenceAgent::OnHttpRequestCompleted);
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb("GET"); // Use "GET" for simple requests, or "POST" for more complex data sending

	// Send the HTTP request
	HttpRequest->ProcessRequest();
}

// ------------------------------------------------------------------------------------------------

void UBraintelligenceAgent::OnHttpRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response,
                                                   bool bWasSuccessful)
{
	FString ResponseContent;
	if (bWasSuccessful && Response.IsValid())
	{
		// Get the HTTP response status code
		const int32 ResponseCode = Response->GetResponseCode();

		// Get the response content as a string
		ResponseContent = Response->GetContentAsString();

		// Do something with the response, e.g., print it to the log
		UE_LOG(LogTemp, Warning, TEXT("HTTP Request completed with status code %d"), ResponseCode);
		UE_LOG(LogTemp, Warning, TEXT("Response content: %s"), *ResponseContent);
	}
	else
	{
		// Handle the case when the request was not successful
		UE_LOG(LogTemp, Error, TEXT("HTTP Request failed!"));
	}

	ConnectWebSocket(ResponseContent);
}

// ------------------------------------------------------------------------------------------------

void UBraintelligenceAgent::ConnectWebSocket(const FString& Address)
{
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}

	const FString Add = "ws://" + Address;
	WebSocket = FWebSocketsModule::Get().CreateWebSocket(Add);

	WebSocket->OnConnected().AddLambda([]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Successfully connected");
	});

	WebSocket->OnConnectionError().AddLambda([](const FString& Error)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
	});

	WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red,
		                                 "Connection Closed " + Reason);
		//GetWorldTimerManager().ClearTimer(TimerHandle_MyFunction);
	});

	WebSocket->OnMessage().AddLambda([](const FString& Message)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Message received: " + Message);
	});

	WebSocket->OnMessageSent().AddLambda([](const FString& SentMessageString)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Message Sent: " + SentMessageString);
	});

	WebSocket->Connect();
}

// ------------------------------------------------------------------------------------------------

bool UBraintelligenceAgent::SendEvent(const FString& Event, const EBraintelligenceEmotion ExpectedEmotion) const
{
	// Concatenate all the strings.
	if (WebSocket.IsValid() && IsConnected())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sending Message: " + Event);
		// Send the final string
		WebSocket->Send(Event + ", " + UEnum::GetValueAsName(ExpectedEmotion).ToString());
		return true;
	}
	else
		return false;
}

// ------------------------------------------------------------------------------------------------

bool UBraintelligenceAgent::SendBuffer(const void* Data, const int32 Size) const
{
	if (IsConnected())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Magenta, "Sending Buffer with size: " + Size);
		WebSocket->Send(Data, Size, true);
		return true;
	}
	else
		return false;
}

// ------------------------------------------------------------------------------------------------

bool UBraintelligenceAgent::IsConnected() const
{
	return WebSocket->IsConnected();
}

// ------------------------------------------------------------------------------------------------

void UBraintelligenceAgent::TakeInGameScreenshot()
{
	if (WebSocket.IsValid() && IsConnected())
	{
		GEngine->GameViewport->OnScreenshotCaptured().AddUObject(this, &UBraintelligenceAgent::AcceptScreenshot);
		FScreenshotRequest::RequestScreenshot(false);
	}
}

// ------------------------------------------------------------------------------------------------

void UBraintelligenceAgent::AcceptScreenshot(const int32 InSizeX, const int32 InSizeY,
                                             const TArray<FColor>& InImageData) const
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(
		FName("ImageWrapper"));
	const TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);

	if (!ImageWrapper->SetRaw(&InImageData[0], InImageData.Num() * sizeof(FColor), InSizeX, InSizeY, ERGBFormat::BGRA,
	                          8))
	{
		return;
	}

	TArray64<uint8> CompressedImage = ImageWrapper->GetCompressed(90);

	const uint8* DataPtr = CompressedImage.GetData();

	// Cast the uint8 pointer to const void*
	const void* VoidPtr = static_cast<const void*>(DataPtr);

	const int32 Size = CompressedImage.Num();

	if (!SendBuffer(VoidPtr, Size))
	{
		// print something about why failed sending the screenshot!
	}

	GEngine->GameViewport->OnScreenshotCaptured().RemoveAll(this);
}

// ------------------------------------------------------------------------------------------------

FString UBraintelligenceAgent::GetKey() const
{
	const UBraintelligenceSettings* BraintelligenceSettings = GetMutableDefault<UBraintelligenceSettings>();

	return BraintelligenceSettings->Key;
}

// ------------------------------------------------------------------------------------------------

void UBraintelligenceAgent::Shutdown() const
{
	if (WebSocket && WebSocket->IsConnected())
	{
		WebSocket->Close();
	}
}

// ------------------------------------------------------------------------------------------------
