#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SBHPlayerController.generated.h"

UCLASS(Abstract, Blueprintable)
class SBH_API ASBHPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASBHPlayerController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Controller|UI", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PlayerCharacterWidget;
	
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUserWidget> PlayerCharacterWidgetInstance;
};
