// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Star.h"

#include "../PlatformerAssignmentCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundCue.h"

AStar::AStar()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AStar::OnComponentBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AStar::OnComponentEndOverlap);

	
}

void AStar::BeginPlay()
{
	Super::BeginPlay();
}

void AStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStar::RotateItem(float DeltaTime)
{
	Super::RotateItem(DeltaTime);
}

void AStar::FloatUpAndDown(float DeltaTime)
{
	Super::FloatUpAndDown(DeltaTime);
}

void AStar::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnComponentBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APlatformerAssignmentCharacter* PlayerCharacter = Cast<APlatformerAssignmentCharacter>(OtherActor);

	if(PlayerCharacter)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Actor Overlap Begin"));
		UE_LOG(LogTemp, Warning, TEXT("Actor Overlap Begin"));

		if(SoundCue)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), SoundCue);
		}
		UStatsComponent* StatsComponent = PlayerCharacter->GetStatsComponent();
		if (StatsComponent)
		{
			StatsComponent->AddStars(1);
			UKismetSystemLibrary::PrintString(GetWorld(), FString(TEXT("Stars: ")) + FString::FromInt(StatsComponent->GetStars()));
		}
		Destroy();
	}
}

void AStar::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnComponentEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	APlatformerAssignmentCharacter* PlayerCharacter = Cast<APlatformerAssignmentCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Actor Overlap End"));
		UE_LOG(LogTemp, Warning, TEXT("Actor Overlap End"));
	}
}


