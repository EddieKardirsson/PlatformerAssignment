// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatsComponent.h"

#include "Kismet/KismetSystemLibrary.h"

#include "../PlatformerAssignmentCharacter.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	SetName("Insert Name in Blueprint");
	SetMaxHealth(100);
	SetMaxStamina(100);
	SetHealth(GetMaxHealth());	
	SetStamina(GetMaxStamina());
	SetCoins(0);
	SetStars(0);
	
	StaminaDrainRate = 25;
	StaminaRegenerationRate = 5;
}


	// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	AActor* Owner = GetOwner();
	if(Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UStatsComponent::OnTakeAnyDamage);
	}
	
	// TODO: Function needed to reload stats
	
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// TODO: Function to regenerate stamina over time while not sprinting
	APlatformerAssignmentCharacter* Character = Cast<APlatformerAssignmentCharacter>(GetOwner());
	if (CheckIfSprinting() && CheckIfMoving() && Character->GetStatsComponent()->GetStamina() > 0)
	{
		DrainStamina(DeltaTime);
		Character->SetIsMoving(false);
	}
	else
	{
		RegenerateStamina(DeltaTime);
	}

	FString OutputMessage = FString(TEXT("Stamina: ") + FString::FromInt(GetStamina()));

	//UKismetSystemLibrary::PrintString(GetWorld(), OutputMessage);
	
}

bool UStatsComponent::CheckIfSprinting() const
{
	APlatformerAssignmentCharacter* Character = Cast<APlatformerAssignmentCharacter>(GetOwner());

	if (Character)
	{
		return Character->GetIsSprinting();
	}
	else return false;
}

bool UStatsComponent::CheckIfMoving() const
{
	APlatformerAssignmentCharacter* Character = Cast<APlatformerAssignmentCharacter>(GetOwner());

	if (Character)
	{
		return Character->GetIsMoving();
	}
	else return false;
}


void UStatsComponent::DrainStamina(float DeltaTime)
{
	//Stats.Stamina -= StaminaDrainRate * DeltaTime;
	AddStamina(-StaminaDrainRate * DeltaTime);
}

void UStatsComponent::RegenerateStamina(float DeltaTime)
{
	if (GetStamina() < GetMaxStamina())
		AddStamina(StaminaRegenerationRate * DeltaTime);
		//Stats.Stamina += StaminaRegenerationRate * DeltaTime;
}

void UStatsComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage < 0)
	{
		return;
	}

	SetHealth(FMath::Clamp(GetHealth() - Damage, -1, GetMaxHealth()));
	//Stats.Health = FMath::Clamp(Stats.Health - Damage, 0, Stats.MaxHealth);

	APlatformerAssignmentCharacter* Character = Cast<APlatformerAssignmentCharacter>(DamagedActor);
	if(Character)
	{
		if (GetHealth() <= 0) Character->SetIsAlive(false);
	}
}


