#include "InventoryComponent.h"

#include "ItemData.h"
#include "SBH/SBHLogChannels.h"

UInventoryComponent::UInventoryComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

TArray<FInventoryItem> UInventoryComponent::GetContents()
{
	return Contents;
}

bool UInventoryComponent::AddItem(UItemData* ItemData, const int Quantity)
{
	UE_LOG(LogSBHInventory, Log, TEXT("AddItem called with ItemData: %s, Quantity: %d"), *ItemData->ToString(), Quantity);
	
	if (IsValid(ItemData))
	{
		for (auto& Item : Contents)
		{
			if (Item.Data->GetFName() == ItemData->GetFName())
			{
				Item.Quantity += Quantity;
				OnContentsUpdated.Broadcast();
				return true;
			}
		}
	
		FInventoryItem NewItem;
		NewItem.Data = ItemData;
		NewItem.Quantity = Quantity;
		Contents.Add(NewItem);
		OnContentsUpdated.Broadcast();
		return true;	
	}

	return false;
}

bool UInventoryComponent::RemoveItem(UItemData* ItemData, const int Quantity)
{
	UE_LOG(LogSBHInventory, Log, TEXT("RemoveItem called with ItemData: %s, Quantity: %d"), *ItemData->ToString(), Quantity);
	
	if (IsValid(ItemData))
	{
		for (int i = 0; i < Contents.Num(); ++i)
		{
			if (Contents[i].Data->GetFName() == ItemData->GetFName())
			{
				Contents[i].Quantity -= FMath::Max(Quantity, 1);

				if (Contents[i].Quantity <= 0)
				{
					Contents.RemoveAt(i);
				}

				OnContentsUpdated.Broadcast();
				return true;
			}
		}
	}

	return false;
}

FInventoryItem UInventoryComponent::GetItem(UItemData* ItemData)
{
	UE_LOG(LogSBHInventory, Log, TEXT("GetItem called with ItemData: %s"), *ItemData->ToString());
	
	if (IsValid(ItemData))
	{
        for (const auto& Item : Contents)
        {
            if (Item.Data->GetFName() == ItemData->GetFName())
            {
                return Item;
            }
        }	
	}
	
	return FInventoryItem();
}
