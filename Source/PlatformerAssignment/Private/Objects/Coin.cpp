// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Coin.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundCue.h"
#include "../PlatformerAssignmentCharacter.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//bIsFloating = true;

	//StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	//SetRootComponent(StaticMesh);
	//StaticMesh->SetGenerateOverlapEvents(false);

	//ArrowOffset = FVector(10, 0, 0);

	//ArrowComponent = CreateDefaultSubobject<UArrowComponent>("Arrow");
	//ArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//ArrowComponent->ArrowColor = FColor::Cyan;
	//ArrowComponent->AddRelativeLocation(ArrowOffset);	

	//RotationSpeed = 256;
	//FloatingSpeed = 1;
	//Height = 100;

	//SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	//SphereComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//SphereComponent->SetSphereRadius(48);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnComponentBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ACoin::OnComponentEndOverlap);

}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//RotateCoin(DeltaTime);
	//
	//if(bIsFloating) FloatUpAndDown(DeltaTime);
}

//void ACoin::RotateCoin(float DeltaTime)
//{
//	CoinRotator = FRotator(0, RotationSpeed, 0) * DeltaTime;
//
//	this->AddActorLocalRotation(CoinRotator);
//}


void ACoin::RotateItem(float DeltaTime)
{
	Super::RotateItem(DeltaTime);
}

void ACoin::FloatUpAndDown(float DeltaTime)
{

	Super::FloatUpAndDown(DeltaTime);

	//FloatingLocation = GetActorLocation();
	//float DeltaHeight = (FMath::Sin(Timer + DeltaTime) - FMath::Sin(Timer)) * FloatingSpeed;

	//FloatingLocation.Z += DeltaHeight * Height;

	//Timer += DeltaTime * FloatingSpeed;

	//SetActorLocation(FloatingLocation);
}

void ACoin::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	Super::OnComponentBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APlatformerAssignmentCharacter* PlayerCharacter = Cast<APlatformerAssignmentCharacter>(OtherActor);

	if(PlayerCharacter)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Actor Overlap Begin!"));
		UE_LOG(LogTemp, Warning, TEXT("Actor Overlap Begin!"));
		
		if(SoundCue)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), SoundCue);
		}
		// TODO: Add coin to player
		UStatsComponent* StatsComponent = PlayerCharacter->GetStatsComponent();
		if (StatsComponent)
		{
			StatsComponent->AddCoins(1);
			UKismetSystemLibrary::PrintString(GetWorld(), FString(TEXT("Coins: ")) + FString::FromInt(StatsComponent->GetCoins()));
		}
		Destroy();
	}
}

void ACoin::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnComponentEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	APlatformerAssignmentCharacter* PlayerCharacter = Cast<APlatformerAssignmentCharacter>(OtherActor);

	if(PlayerCharacter)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Actor Overlap End!"));
		UE_LOG(LogTemp, Warning, TEXT("Actor Overlap End!"));
	}
}

