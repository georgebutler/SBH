#include "EquipmentInstance.h"

#include "GameFramework/Character.h"
#include "SBH/SBHLogChannels.h"

AEquipmentInstance::AEquipmentInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEquipmentInstance::Equip_Implementation(ACharacter* Character)
{
	UE_LOG(LogSBHEquipment, Log, TEXT("Equip on %s called with Character: %s"), *GetName(), *Character->GetName());

	EquippedCharacter = Character;
	SetActorEnableCollision(false);
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), AttachmentRules, AttachmentSocket);
}


void AEquipmentInstance::Unequip_Implementation()
{
	UE_LOG(LogSBHEquipment, Log, TEXT("Unequip on %s called with Character: %s"), *GetName(), *EquippedCharacter->GetName());

	EquippedCharacter = nullptr;
	Destroy();
}