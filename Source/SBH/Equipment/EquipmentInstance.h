#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EquipmentInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnequipped);

UCLASS(BlueprintType, Blueprintable)
class SBH_API AEquipmentInstance : public AActor
{
	GENERATED_BODY()

public:
	AEquipmentInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(BlueprintAssignable)
	FOnEquipped OnEquipped;

	UPROPERTY(BlueprintAssignable)
	FOnUnequipped OnUnequipped;
};
