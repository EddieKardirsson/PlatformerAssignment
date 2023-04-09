// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformerAssignmentGameMode.h"
#include "PlatformerAssignmentCharacter.h"
#include "GameFramework/HUD.h"
#include "UObject/ConstructorHelpers.h"

APlatformerAssignmentGameMode::APlatformerAssignmentGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Game/Blueprints/BP_PlatformCharacter"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUD_BPClass(TEXT("/Game/Game/Blueprints/UI/BP_HUD"));
	if(PlayerHUD_BPClass.Class != NULL)
	{
		HUDClass = PlayerHUD_BPClass.Class;
	}

	
}

void APlatformerAssignmentGameMode::BeginPlay()
{
	Super::BeginPlay();
		
}





