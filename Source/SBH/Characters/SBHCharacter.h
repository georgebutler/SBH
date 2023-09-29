#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "SBHCharacter.generated.h"

class UStatsComponent;

UCLASS(Abstract, Blueprintable)
class SBH_API ASBHCharacter : public AModularCharacter
{
	GENERATED_BODY()

public:
	ASBHCharacter();

	UStatsComponent* GetStatsComponent() const;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStatsComponent> StatsComponent;
};
