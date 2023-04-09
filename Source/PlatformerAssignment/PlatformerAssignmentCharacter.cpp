// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformerAssignmentCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlatformerAssignmentGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/StatsComponent.h"



//////////////////////////////////////////////////////////////////////////
// APlatformerAssignmentCharacter

APlatformerAssignmentCharacter::APlatformerAssignmentCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// Double Jump! - as class default. 
	JumpMaxCount = 2;

	StatsComponent = CreateDefaultSubobject<UStatsComponent>("StatsComponent");
	bIsSprinting = false;
	bIsMoving = false;
	bIsPaused = false;
	bIsAlive = true;

	JumpStaminaCost = 10;
}

void APlatformerAssignmentCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	AddDefaultMappingContext();

	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	SprintSpeed = GetCharacterMovement()->MaxWalkSpeed * 2;

	APlatformerAssignmentGameMode* GameMode = Cast <APlatformerAssignmentGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->SpawnTransform.SetLocation(GetActorTransform().GetLocation());
		GameMode->SpawnTransform.SetRotation(GetActorTransform().GetRotation());
	}
}

void APlatformerAssignmentCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UKismetSystemLibrary::PrintString(GetWorld(), FString(TEXT("Speed: ")) +FString::FromInt(GetMovementComponent()->GetMaxSpeed()));
	if (StatsComponent->GetStamina() <= 0)
	{
		SetIsSprinting(false);
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}

	if(!bIsAlive)
	{
		DeactivateHUD();
		this->Destroy();
	} 
}



//////////////////////////////////////////////////////////////////////////
// Input

void APlatformerAssignmentCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlatformerAssignmentCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlatformerAssignmentCharacter::Look);

		//Sprinting		
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &APlatformerAssignmentCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlatformerAssignmentCharacter::StopSprint);

		EnhancedInputComponent->BindAction(OpenPauseMenuAction, ETriggerEvent::Started, this, &APlatformerAssignmentCharacter::OpenPauseMenu);

		EnhancedInputComponent->BindAction(NavigateMenuAction, ETriggerEvent::Started, this, &APlatformerAssignmentCharacter::NavigateMenu);
	}

}

void APlatformerAssignmentCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
		
	if (Controller != nullptr)
	{
		SetIsMoving(true);
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}	
}

void APlatformerAssignmentCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlatformerAssignmentCharacter::Sprint()
{	
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();

	if (!MovementComponent) return;	

	if(StatsComponent->GetStamina() >= 1)
		SetIsSprinting(true);

	const float MaxWalkSpeed = MovementComponent->MaxWalkSpeed;

	if((StatsComponent->GetStamina() < 1) && bIsSprinting)
	{		
		MovementComponent->MaxWalkSpeed = WalkSpeed;
		SetIsSprinting(false);
	}
	else if (bIsSprinting) {
		MovementComponent->MaxWalkSpeed = SprintSpeed;
	}

}

void APlatformerAssignmentCharacter::StopSprint()
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();

	if (!MovementComponent) return;
	
	if (bIsSprinting) {
		const float MaxWalkSpeed = MovementComponent->MaxWalkSpeed;
		MovementComponent->MaxWalkSpeed = WalkSpeed;
		SetIsSprinting(false);
	}
	
}

void APlatformerAssignmentCharacter::Jump()
{
	if (GetStatsComponent()->GetStamina() < JumpStaminaCost) return;

	Super::Jump();

	if(JumpSound)
		UGameplayStatics::PlaySound2D(GetWorld(), JumpSound);

	GetStatsComponent()->AddStamina(-JumpStaminaCost);
}


void APlatformerAssignmentCharacter::AddDefaultMappingContext()
{
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);			
		}
	}
}

void APlatformerAssignmentCharacter::AddPauseMenuMappingContext()
{
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PauseMenuMappingContext, 1);
		}
	}
}

void APlatformerAssignmentCharacter::RemovePauseMenuMappingContext()
{
	if(APlayerController* PlayerController=Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(PauseMenuMappingContext);
		}
	}
}


