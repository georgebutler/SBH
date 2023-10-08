#include "WeaponInstance.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "KismetTraceUtils.h"
#include "Animation/AnimInstanceProxy.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
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
	if (const APlayerController* PlayerController = Cast<APlayerController>(EquippedCharacter->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(InputMappingContext);
		}
	}

	Super::Unequip_Implementation();
}

void AWeaponInstance::FirePrimary()
{
	if (!EquippedCharacter) { return; }
	
	FVector Start, End;
	FRotator EyeRotation;
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(EquippedCharacter);

	EquippedCharacter->GetActorEyesViewPoint(Start, EyeRotation);
	End = Start + EyeRotation.Vector() * FirePrimaryRange;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
	DrawDebugLineTraceSingle(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, EDrawDebugTrace::ForDuration, true, HitResult, FColor(255, 0, 0), FColor(255, 0, 0), 1.0f);
	
	if(HitResult.bBlockingHit)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			UE_LOG(LogSBHEquipment, Verbose, TEXT("Hit Actor: %s"), *HitActor->GetName());
			UGameplayStatics::ApplyPointDamage(HitActor, FirePrimaryDamage, HitResult.Normal * -1.0f, HitResult, EquippedCharacter->GetController(), this, PrimaryDamageType);
		}
	}
}

void AWeaponInstance::BeginFirePrimary_Implementation(const FInputActionValue& Input)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("BeginFirePrimary_Implementation"));

	switch (FiringMode)
	{
	case EWeaponFiringMode::SemiAutomatic:
		FirePrimary();
		break;
	case EWeaponFiringMode::Automatic:
		GetWorld()->GetTimerManager().SetTimer(FirePrimaryTimerHandle, this, &AWeaponInstance::FirePrimary, FirePrimaryDelay, true);
		break;
	default:
		break;
	}
	
}

void AWeaponInstance::EndFirePrimary_Implementation(const FInputActionValue& Input)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("EndFirePrimary_Implementation"));
	GetWorld()->GetTimerManager().ClearTimer(FirePrimaryTimerHandle);
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

