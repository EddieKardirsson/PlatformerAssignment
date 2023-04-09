// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerAssignmentGameMode.generated.h"

UCLASS(minimalapi)
class APlatformerAssignmentGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APlatformerAssignmentGameMode();


protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Respawn", meta = (AllowPrivateAccess = "true"))
	FTransform SpawnTransform;


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RespawnPlayer(ACharacter* Player);

};



