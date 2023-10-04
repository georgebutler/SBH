#pragma once

#include "CoreMinimal.h"
#include "SBH/Equipment/EquipmentInstance.h"
#include "WeaponInstance.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SBH_API AWeaponInstance : public AEquipmentInstance
{
	GENERATED_BODY()

public:
	AWeaponInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};