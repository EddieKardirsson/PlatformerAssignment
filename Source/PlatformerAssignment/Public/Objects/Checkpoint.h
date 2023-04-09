// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Checkpoint.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERASSIGNMENT_API ACheckpoint : public ATriggerVolume
{
	GENERATED_BODY()

private:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	FTransform Transform{};

public:

	ACheckpoint();

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);	

	
};
