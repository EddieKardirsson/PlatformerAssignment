// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableItem.h"
#include "Coin.generated.h"

UCLASS()
class PLATFORMERASSIGNMENT_API ACoin : public APickableItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

protected:

	///** The mesh for the coin */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess))
	//	UStaticMeshComponent* StaticMesh;

	///** Forward vector of this object*/
	//UPROPERTY()
	//	class UArrowComponent* ArrowComponent;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SphereCollider", meta = (AllowPrivateAccess))
	//	class USphereComponent* SphereComponent;

private:

	///** The rotation speed for the coin */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess))
	//	float RotationSpeed;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess))
	//	bool bIsFloating;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess))
	//	float FloatingSpeed;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess))
	//	float Height;

	//float Timer = 0;

	//FVector ArrowOffset;

	///** private Rotator for the coin */
	//FRotator CoinRotator;

	///** private Vector for the coin floating offset */
	//FVector FloatingLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	//UFUNCTION()
	//	void RotateCoin(float DeltaTime);

	
	virtual void RotateItem(float DeltaTime) override;

	
	virtual void FloatUpAndDown(float DeltaTime) override;

	
	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	
	virtual void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
};
