#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

USTRUCT(BlueprintType)
struct FInteractionInfo
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCanInteract;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText InteractionText;
};

UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class SBH_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	FInteractionInfo GetInteractionInfo();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	void OnInteract(AActor* InteractionActor);
};
