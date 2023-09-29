#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SBHGameMode.generated.h"

UCLASS(Abstract, Blueprintable)
class SBH_API ASBHGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASBHGameMode();
};
