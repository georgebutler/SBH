#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "Components/PawnComponent.h"
#include "InventoryComponent.generated.h"

class UItemData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnContentsUpdated);

USTRUCT(BlueprintType, Blueprintable)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UItemData> Data = nullptr;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int Quantity = 0;

	bool operator == (const FInventoryItem& OtherItem) const
	{
		return OtherItem.Data->GetClass() == Data->GetClass();
	}
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SBH_API UInventoryComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable)
	FOnContentsUpdated OnContentsUpdated;
	
	UFUNCTION(BlueprintCallable)
	TArray<FInventoryItem> GetContents();

	UFUNCTION(BlueprintCallable)
	bool AddItem(UItemData* ItemData, int Quantity);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(UItemData* ItemData, int Quantity);
	
	UFUNCTION(BlueprintCallable)
	FInventoryItem GetItem(UItemData* ItemData);
	
private:
	UPROPERTY()
	TArray<FInventoryItem> Contents;
};
