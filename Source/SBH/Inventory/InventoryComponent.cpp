#include "InventoryComponent.h"

#include "ItemData.h"

UInventoryComponent::UInventoryComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

TArray<FInventoryItem> UInventoryComponent::GetContents()
{
	return Contents;
}

bool UInventoryComponent::AddItem(UItemData* ItemData, int Quantity)
{
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

bool UInventoryComponent::RemoveItem(UItemData* ItemData, int Quantity)
{
	if (IsValid(ItemData))
	{
		for (auto& Item : Contents)
		{
			if (Item.Data->GetFName() == ItemData->GetFName())
			{
				Item.Quantity -= FMath::Max(Quantity, 1);
			
				if (Item.Quantity <= 0)
				{
					Contents.Remove(Item);
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
