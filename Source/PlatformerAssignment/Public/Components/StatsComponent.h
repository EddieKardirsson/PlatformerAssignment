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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 Coins;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	FCharacterStats Stats;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenerationRate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
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

	bool CheckIfSprinting() const;
	bool CheckIfMoving() const;

	void DrainStamina(float DeltaTime);
	void RegenerateStamina(float DeltaTime);

protected:

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
