#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "EquipmentManagerComponent.generated.h"

class AEquipmentInstance;
class UEquipmentData;
class UEquipmentInstance;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SBH_API UEquipmentManagerComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY(SaveGame)
	TObjectPtr<UEquipmentData> PrimaryWeapon;
};
