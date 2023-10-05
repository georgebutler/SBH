#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "EquipmentManagerComponent.generated.h"

class UItemData;
class AEquipmentInstance;
class UEquipmentData;
class UEquipmentInstance;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SBH_API UEquipmentManagerComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure)
	static UEquipmentManagerComponent* FindEquipmentManagerComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UEquipmentManagerComponent>() : nullptr); }

	UFUNCTION(BlueprintCallable)
	void Equip(UItemData* ItemData, bool bRequiresInInventory = true);

	UFUNCTION(BlueprintCallable)
	void Unequip(UItemData* ItemData);

private:
	UPROPERTY(SaveGame)
	TObjectPtr<UEquipmentData> PrimaryWeapon;
};
