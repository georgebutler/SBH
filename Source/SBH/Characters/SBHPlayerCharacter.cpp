#include "SBHPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SBH/Stats/StatsComponent.h"

ASBHPlayerCharacter::ASBHPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	FVector EyeLocation;
	FRotator EyeRotation;
	APawn::GetActorEyesViewPoint(EyeLocation, EyeRotation);
	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(0, 0, EyeLocation.Z));
	FirstPersonCamera->bUsePawnControlRotation = true;
	
	FirstPersonArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonArms"));
	FirstPersonArms->SetupAttachment(FirstPersonCamera);
	FirstPersonArms->SetRelativeLocation(FVector(0, 0, -160));
	FirstPersonArms->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	FirstPersonArms->CastShadow = false;
}

void ASBHPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UStatsComponent* Stats = GetStatsComponent();
	check(Stats);
	Stats->OnHealthZero.AddDynamic(this, &ASBHPlayerCharacter::OnCharacterDied);
}

void ASBHPlayerCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASBHPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(InputMappingContext);
			Subsystem->AddMappingContext(InputMappingContext, 0);

			UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
			check(EnhancedInput);
			
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASBHPlayerCharacter::Move);
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASBHPlayerCharacter::Look);
			EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ASBHPlayerCharacter::Jump);
			EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASBHPlayerCharacter::StopJumping);
		}
	}
}

void ASBHPlayerCharacter::DestroyPlayerInputComponent()
{
	Super::DestroyPlayerInputComponent();

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(InputMappingContext);
		}
	}
}

void ASBHPlayerCharacter::FellOutOfWorld(const UDamageType& DmgType)
{
	OnCharacterDied();
}

void ASBHPlayerCharacter::OnCharacterDied()
{
	OnDied.Broadcast();
	
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->StopMovementImmediately();
	CharacterMovementComponent->DisableMovement();
	
	GetWorldTimerManager().SetTimer(TimerHandleRespawn, this, &ASBHPlayerCharacter::OnCharacterRespawned, 3.0f, false);
}

void ASBHPlayerCharacter::OnCharacterRespawned()
{
	ASBHPlayerCharacter* NewCharacter = CastChecked<ASBHPlayerCharacter>(GetWorld()->SpawnActor(PlayerCharacter));
	AController* CurrentController = GetController();

	DetachFromControllerPendingDestroy();
	CurrentController->Possess(NewCharacter);
	OnRespawned.Broadcast(NewCharacter);
	Destroy();
}

void ASBHPlayerCharacter::Move(const FInputActionValue& Input)
{
	const FVector2D InputValue = Input.Get<FVector2D>();
	
	FRotator Rotation = GetControlRotation();
	Rotation.Pitch = 0.0f;
	Rotation.Roll = 0.0f;
	AddMovementInput(UKismetMathLibrary::GetForwardVector(Rotation), InputValue.Y);

	Rotation = GetControlRotation();
	Rotation.Pitch = 0.0f;
	AddMovementInput(UKismetMathLibrary::GetRightVector(Rotation), InputValue.X);
}

void ASBHPlayerCharacter::Look(const FInputActionValue& Input)
{
	const FVector2D InputValue = Input.Get<FVector2D>();
	
	AddControllerYawInput(InputValue.X);
	AddControllerPitchInput(InputValue.Y);
}

