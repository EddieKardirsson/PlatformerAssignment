// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/PickableItem.h"

#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../PlatformerAssignmentCharacter.h"



// Sets default values
APickableItem::APickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsFloating = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
	StaticMesh->SetGenerateOverlapEvents(false);

	ArrowOffset = FVector(10, 0, 0);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("Arrow");
	ArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ArrowComponent->ArrowColor = FColor::Cyan;
	ArrowComponent->AddRelativeLocation(ArrowOffset);

	RotationSpeed = 256;
	FloatingSpeed = 1;
	Height = 100;
	StaminaReplenishmentAmount = 10;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	SphereComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SphereComponent->SetSphereRadius(48);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickableItem::OnComponentBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &APickableItem::OnComponentEndOverlap);		
}

// Called when the game starts or when spawned
void APickableItem::BeginPlay()
{
	Super::BeginPlay();

	if(!SoundCue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sound Cue is missing! Please add a Cue"));
	}
}

// Called every frame
void APickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateItem(DeltaTime);

	if (bIsFloating) FloatUpAndDown(DeltaTime);
}

void APickableItem::RotateItem(float DeltaTime)
{
	ItemRotator = FRotator(0, RotationSpeed, 0) * DeltaTime;
	AddActorLocalRotation(ItemRotator);
}

void APickableItem::FloatUpAndDown(float DeltaTime)
{
	FloatingLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(Timer + DeltaTime) - FMath::Sin(Timer)) * FloatingSpeed;

	FloatingLocation.Z += DeltaHeight * Height;

	Timer += DeltaTime * FloatingSpeed;

	SetActorLocation(FloatingLocation);
}

void APickableItem::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Baseclass Overlap Begin!"));

	APlatformerAssignmentCharacter* PlayerCharacter = Cast<APlatformerAssignmentCharacter>(OtherActor);
	if(PlayerCharacter)
	{
		PlayerCharacter->GetStatsComponent()->AddStamina(StaminaReplenishmentAmount);
	}
}

void APickableItem::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Baseclass Overlap End!"));
}




