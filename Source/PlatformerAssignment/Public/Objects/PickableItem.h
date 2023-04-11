// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StatsComponent.h"
#include "Containers/UnrealString.h"

#include "PickableItem.generated.h"


UCLASS()
class PLATFORMERASSIGNMENT_API APickableItem : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APickableItem();

protected:

	/** The mesh for the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess))
		UStaticMeshComponent* StaticMesh;

	/** Forward vector of this object*/
	UPROPERTY()
		class UArrowComponent* ArrowComponent;

	/** The collider for the overlap events */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SphereCollider", meta = (AllowPrivateAccess))
		class USphereComponent* SphereComponent;

	/** Reference to a Sound Cue object. Insert the corresponding SC_<FileName> in Blueprints */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess))
		class USoundCue* SoundCue;

private:

	/** The rotation speed for the item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess))
		float RotationSpeed;

	/** Turn on/off if the object should float along the z-axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess))
		bool bIsFloating;

	/** Set the floating speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess))
		float FloatingSpeed;

	/** The height factor multiplied in for the floating formula */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess))
		float Height;

	/** Amount of Stamina being replenished when player collects the item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess))
		float StaminaReplenishmentAmount;

	/** The timer member variable */
	float Timer = 0;

	/** The ArrowComponent offset position. Default will be 10 Unreal units along the forward vector (X-axis) */
	FVector ArrowOffset;

	/** private Rotator for the item */
	FRotator ItemRotator;

	/** private Vector for the item floating offset */
	FVector FloatingLocation;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:

	/** This function Rotates the item by the factor of RotationSpeed along the Z-Axis (Yaw) */
	UFUNCTION()
		virtual void RotateItem(float DeltaTime);

	/** This function floats the item up and down given the FloatingSpeed and Height factors */
	UFUNCTION()
		virtual void FloatUpAndDown(float DeltaTime);

	/** Delegate-bound function for component begin overlap */
	UFUNCTION()
		virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/** Delegate-bound function for component end overlap */
	UFUNCTION()
		virtual void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};


