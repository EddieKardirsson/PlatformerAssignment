// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

public:

	/** The character name, insert the name in Blueprints if you want to create more playable characters
	 * than UE5-Quinn that is the default playable character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	FName Name;

	/** The maximum amount of health */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	/** The maximum amount of stamina */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float MaxStamina;

	/** Current health of the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float Health;

	/** Current stamina of the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float Stamina;

	/** Amount of coins collected */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 Coins;

	/** Amount of stars collected */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 Stars;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMERASSIGNMENT_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

private:

	/** Variable for player Stats that are to be stored */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	FCharacterStats Stats;

	/** The rate per second the Stamina is drained (while sprinting) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float StaminaDrainRate;

	/** The rate per second Stamina is replenished (while not sprinting and when not jumping) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenerationRate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Helper functions for getting and setting the FCharacterStats below
	
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetName(const FName InName) { Stats.Name = InName; }
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetMaxHealth(const float InHealth) { Stats.MaxHealth = InHealth; }
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetMaxStamina(const float InStamina) { Stats.MaxStamina = InStamina; }
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetHealth(const float InHealth) { Stats.Health = InHealth; }
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetStamina(const float InStamina) { Stats.Stamina = InStamina; }
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetCoins(const int32 InCoins) { Stats.Coins = InCoins; }
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetStars(const int32 InStars) { Stats.Stars = InStars; }

	UFUNCTION(BlueprintCallable, BlueprintPure) FORCEINLINE FName& GetName() { return Stats.Name; }
	UFUNCTION(BlueprintCallable, BlueprintPure) FORCEINLINE float& GetMaxHealth() { return Stats.MaxHealth; }
	UFUNCTION(BlueprintCallable, BlueprintPure) FORCEINLINE float& GetMaxStamina() { return Stats.MaxStamina; }
	UFUNCTION(BlueprintCallable, BlueprintPure) FORCEINLINE float& GetHealth() { return Stats.Health; }
	UFUNCTION(BlueprintCallable, BlueprintPure) FORCEINLINE float& GetStamina() { return Stats.Stamina; }
	UFUNCTION(BlueprintCallable, BlueprintPure) FORCEINLINE int32& GetCoins() { return Stats.Coins; }
	UFUNCTION(BlueprintCallable, BlueprintPure) FORCEINLINE int32& GetStars() { return Stats.Stars; }
	
	UFUNCTION(BlueprintCallable) FORCEINLINE void AddHealth(const float InHealth) { Stats.Health += InHealth; }
	UFUNCTION(BlueprintCallable) FORCEINLINE void AddStamina(const float InStamina) { Stats.Stamina += InStamina; if (Stats.Stamina > Stats.MaxStamina) Stats.Stamina = Stats.MaxStamina; }
	UFUNCTION(BlueprintCallable) FORCEINLINE void AddCoins(const int32 InCoins) { Stats.Coins += InCoins; }
	UFUNCTION(BlueprintCallable) FORCEINLINE void AddStars(const int32 InStars) { Stats.Stars += InStars; }

private:

	// Boolean checks returning true or false depending on the corresponding conditions.
	bool CheckIfSprinting() const;
	bool CheckIfMoving() const;

	// This function activates when player is sprinting
	void DrainStamina(float DeltaTime);
	// This function is always active except when sprinting
	void RegenerateStamina(float DeltaTime);

protected:

	/** Delegate-bound function that fires off when taking damage */
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
