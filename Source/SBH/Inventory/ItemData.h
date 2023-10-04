#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SBH_API UItemData : public UDataAsset
{
	GENERATED_BODY()

public:
	UItemData();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText DisplayName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText DisplayDescription;
};
