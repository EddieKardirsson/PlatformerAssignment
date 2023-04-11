// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlatformerAssignmentCharacter.generated.h"


UCLASS(config=Game)
class APlatformerAssignmentCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;


	/** Pause Menu Mapping Context */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* PauseMenuMappingContext;

	/** Open Pause Menu*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* OpenPauseMenuAction;

	/** Close Pause Menu */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* NavigateMenuAction;

	/** Reference to Sound Cue for jump-sound. Insert the corresponding asset */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	class USoundCue* JumpSound;

	/** Cached reference to the UStatsComponent that holds the stats of the player */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	class UStatsComponent* StatsComponent;
		

public:
	APlatformerAssignmentCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Sprint();

	void StopSprint();

	/** Pauses the game when called, implemented in Blueprints */
	UFUNCTION(BlueprintImplementableEvent)
	void OpenPauseMenu();

	/** Navigating on pause menu, implemented in Blueprints */
	UFUNCTION(BlueprintImplementableEvent)
	void NavigateMenu(const FInputActionValue& Value);
	

			
private:

	bool bIsMoving;
	bool bIsSprinting;
	bool bIsPaused;
	bool bIsAlive;

	float WalkSpeed;
	float SprintSpeed;

	/** How much each jump costs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float JumpStaminaCost;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:

	virtual void Jump() override;



public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UStatsComponent* GetStatsComponent() { return StatsComponent; }

	FORCEINLINE bool GetIsSprinting() { return bIsSprinting; }
	FORCEINLINE void SetIsSprinting(bool bInIsSprinting) { bIsSprinting = bInIsSprinting; }

	FORCEINLINE bool GetIsMoving() { return bIsMoving; }
	FORCEINLINE void SetIsMoving(bool bInIsMoving) { bIsMoving = bInIsMoving; }

	UFUNCTION(BlueprintCallable, BlueprintPure) FORCEINLINE bool GetIsAlive() const { return bIsAlive; }
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetIsAlive(bool bInIsAlive) { bIsAlive = bInIsAlive; }

	UFUNCTION()
	void AddDefaultMappingContext();

	UFUNCTION(BlueprintCallable)
	void AddPauseMenuMappingContext();

	UFUNCTION(BlueprintCallable)
	void RemovePauseMenuMappingContext();

	UFUNCTION(BlueprintImplementableEvent)
	void DeactivateHUD();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AfterDestroyed();
	

};

