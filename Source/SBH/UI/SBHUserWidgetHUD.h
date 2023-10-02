#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBHUserWidgetHUD.generated.h"

class ASBHPlayerCharacter;

UCLASS(Abstract, Blueprintable)
class SBH_API USBHUserWidgetHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<ASBHPlayerCharacter> PlayerCharacterInstance;

protected:
	virtual void NativeConstruct() override;
};
