#include "WeaponInstance.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "SBH/SBHLogChannels.h"

AWeaponInstance::AWeaponInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AWeaponInstance::Equip_Implementation(ACharacter* Character)
{
	Super::Equip_Implementation(Character);

	if (const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(InputMappingContext);
			Subsystem->AddMappingContext(InputMappingContext, 0);

			UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
			check(EnhancedInput);
			
			EnhancedInput->BindAction(PrimaryFireAction, ETriggerEvent::Started, this, &AWeaponInstance::BeginFirePrimary);
			EnhancedInput->BindAction(PrimaryFireAction, ETriggerEvent::Completed, this, &AWeaponInstance::EndFirePrimary);
			EnhancedInput->BindAction(SecondaryFireAction, ETriggerEvent::Started, this, &AWeaponInstance::BeginFireSecondary);
			EnhancedInput->BindAction(SecondaryFireAction, ETriggerEvent::Completed, this, &AWeaponInstance::EndFireSecondary);
			EnhancedInput->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &AWeaponInstance::Reload);
		}
	}
}

void AWeaponInstance::Unequip_Implementation()
{
	Super::Unequip_Implementation();

	check(EquippedCharacter);
	if (const APlayerController* PlayerController = Cast<APlayerController>(EquippedCharacter->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(InputMappingContext);
		}
	}
}

void AWeaponInstance::BeginFirePrimary_Implementation(const FInputActionValue& Input)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("BeginFirePrimary_Implementation"));
}

void AWeaponInstance::EndFirePrimary_Implementation(const FInputActionValue& Input)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("EndFirePrimary_Implementation"));
}

void AWeaponInstance::BeginFireSecondary_Implementation(const FInputActionValue& Input)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("BeginFireSecondary_Implementation"));
}

void AWeaponInstance::EndFireSecondary_Implementation(const FInputActionValue& Input)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("EndFireSecondary_Implementation"));
}

void AWeaponInstance::Reload_Implementation(const FInputActionValue& Input)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("Reload_Implementation"));
}

