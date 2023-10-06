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

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText DisplayName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText DisplayDescription;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UTexture2D> Icon;

	virtual FString ToString() const
	{
		return FString::Printf(TEXT("ItemName: %s"), *GetFName().ToString());
	}
};
