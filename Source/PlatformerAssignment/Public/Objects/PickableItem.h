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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SphereCollider", meta = (AllowPrivateAccess))
		class USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess))
		class USoundCue* SoundCue;

private:

	/** The rotation speed for the coin */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess))
		float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess))
		bool bIsFloating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess))
		float FloatingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess))
		float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess))
		float StaminaReplenishmentAmount;

	float Timer = 0;

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

	UFUNCTION()
		virtual void RotateItem(float DeltaTime);

	UFUNCTION()
		virtual void FloatUpAndDown(float DeltaTime);

	UFUNCTION()
		virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};


