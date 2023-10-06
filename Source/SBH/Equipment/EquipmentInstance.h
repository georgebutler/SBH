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
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName AttachmentSocket;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Equip(ACharacter* Character);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Unequip(ACharacter* Character);
};
