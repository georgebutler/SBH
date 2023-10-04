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
	for (auto& Item : Contents)
	{
		if (Item.Data->GetClass() == ItemData->GetClass())
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

bool UInventoryComponent::RemoveItem(UItemData* ItemData, int Quantity)
{
	for (auto& Item : Contents)
	{
		if (Item.Data->GetClass() == ItemData->GetClass())
		{
			Item.Quantity -= Quantity;
			
			if (Item.Quantity <= 0)
			{
				Contents.Remove(Item);
			}

			OnContentsUpdated.Broadcast();
			return true;
		}
	}

	return false;
}

FInventoryItem UInventoryComponent::GetItem(UItemData* ItemData)
{
	for (const auto& Item : Contents)
	{
		if (Item.Data->GetClass() == ItemData->GetClass())
		{
			return Item;
		}
	}
	
	return FInventoryItem();
}
