#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EquipmentInstance.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SBH_API AEquipmentInstance : public AActor
{
	GENERATED_BODY()

public:
	AEquipmentInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Equip(ACharacter* Character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Unequip(ACharacter* Character);
};
