#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SBH/Inventory/ItemData.h"
#include "EquipmentData.generated.h"

class AEquipmentInstance;

UENUM(BlueprintType)
enum EEquipmentSlot
{
	Weapon,
	Helmet,
	Armor,
	Grenade,
	Consumable,
};

UCLASS(BlueprintType)
class SBH_API UEquipmentData : public UItemData
{
	GENERATED_BODY()

public:
	UEquipmentData();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TEnumAsByte<EEquipmentSlot> EquipmentSlot;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftClassPtr<AEquipmentInstance> SoftClassPtr;

	virtual FString ToString() const override
	{
		return UItemData::ToString() + ", " + FString::Printf(TEXT("EquipmentSlot: %d"), static_cast<int32>(EquipmentSlot));
	}
};
