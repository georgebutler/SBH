#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SBH/Inventory/ItemData.h"
#include "EquipmentData.generated.h"

class AEquipmentInstance;

UCLASS(BlueprintType)
class SBH_API UEquipmentData : public UItemData
{
	GENERATED_BODY()

public:
	UEquipmentData();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftClassPtr<AEquipmentInstance> SoftClassPtr;
};
