// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Checkpoint.h"
#include "../PlatformerAssignmentCharacter.h"
#include "../PlatformerAssignmentGameMode.h"
#include "Kismet/KismetSystemLibrary.h"

ACheckpoint::ACheckpoint()
{
	OnActorBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ACheckpoint::OnOverlapEnd);
}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();

	Transform = GetActorTransform();
}

void ACheckpoint::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor)
	{
		APlatformerAssignmentCharacter* Player = Cast<APlatformerAssignmentCharacter>(OtherActor);
		if(Player)
		{
			APlatformerAssignmentGameMode* PlayerGameMode = Cast<APlatformerAssignmentGameMode>(GetWorld()->GetAuthGameMode());
			if(PlayerGameMode)
			{
				PlayerGameMode->SpawnTransform = this->Transform;
			}
		}
	}
}

void ACheckpoint::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor)
	{
		APlatformerAssignmentCharacter* Player = Cast<APlatformerAssignmentCharacter>(OtherActor);
		if (Player)
		{
			APlatformerAssignmentGameMode* PlayerGameMode = Cast<APlatformerAssignmentGameMode>(GetWorld()->GetAuthGameMode());
			if (PlayerGameMode)
			{
				UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Player exits the Checkpoint"));
			}
		}
	}
}




