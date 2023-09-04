// Copyright Epic Games, Inc. All Rights Reserved.

#include "BRTSDKSampleGameMode.h"
#include "BRTSDKSampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABRTSDKSampleGameMode::ABRTSDKSampleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
