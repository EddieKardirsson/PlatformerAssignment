// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/PickableItem.h"
#include "Star.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERASSIGNMENT_API AStar : public APickableItem
{
	GENERATED_BODY()

public:

	AStar();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

private:


	virtual void RotateItem(float DeltaTime) override;

	virtual void FloatUpAndDown(float DeltaTime) override;

	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
