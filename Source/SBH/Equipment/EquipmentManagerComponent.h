#pragma once

#include "CoreMinimal.h"
#include "EquipmentData.h"
#include "EquipmentInstance.h"
#include "Components/PawnComponent.h"
#include "EquipmentManagerComponent.generated.h"

class UItemData;
class AEquipmentInstance;
class UEquipmentData;
class UEquipmentInstance;

USTRUCT(BlueprintType)
struct FEquippedItem
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UEquipmentData> Data;

	UPROPERTY()
	TObjectPtr<AEquipmentInstance> Instance;

	FString ToString() const
	{
		return FString::Printf(TEXT("Instance: %s, Data: %s"), Instance ? *Instance->GetName() : TEXT("None"), Data ? *Data->GetName() : TEXT("None"));
	}
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SBH_API UEquipmentManagerComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure)
	static UEquipmentManagerComponent* FindEquipmentManagerComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UEquipmentManagerComponent>() : nullptr); }

	UFUNCTION(BlueprintCallable)
	void Equip(UItemData* ItemData);

	UFUNCTION(BlueprintCallable)
	void Unequip(UItemData* ItemData);

	UPROPERTY(BlueprintReadOnly)
	FEquippedItem EquippedPrimaryWeapon;

	UPROPERTY(BlueprintReadOnly)
	FEquippedItem EquippedSecondaryWeapon;

	UPROPERTY(BlueprintReadOnly)
	FEquippedItem EquippedHelmet;

	UPROPERTY(BlueprintReadOnly)
	FEquippedItem EquippedArmor;

	UPROPERTY(BlueprintReadOnly)
	FEquippedItem EquippedGrenade;

	UPROPERTY(BlueprintReadOnly)
	FEquippedItem EquippedConsumable;

private:
	void EquipItem(UEquipmentData* EquipmentData, FEquippedItem& Slot, ACharacter* OwningCharacter);
	void UnequipItem(FEquippedItem& Slot, UEquipmentData* EquipmentData, ACharacter* OwningCharacter);
	
	void EquipWeapon(UEquipmentData* EquipmentData, ACharacter* OwningCharacter);
	void UnequipWeapon(UEquipmentData* EquipmentData, ACharacter* OwningCharacter);
};
