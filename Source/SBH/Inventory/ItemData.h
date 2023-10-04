#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

UCLASS(BlueprintType)
class SBH_API UItemData : public UDataAsset
{
	GENERATED_BODY()

public:
	UItemData();

	UPROPERTY(EditAnywhere)
	FText DisplayName;

	UPROPERTY(EditAnywhere)
	FText DisplayDescription;
};
