#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SBH/Inventory/ItemData.h"
#include "EquipmentData.generated.h"

class AEquipmentInstance;

UCLASS(BlueprintType, Blueprintable)
class SBH_API UEquipmentData : public UItemData
{
	GENERATED_BODY()

public:
	UEquipmentData();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSoftClassPtr<AEquipmentInstance> SoftClassPtr;
};
