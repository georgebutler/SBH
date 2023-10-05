#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionActorChanged, AActor*, OldActor, AActor*, NewActor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SBH_API UInteractionComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure)
	static UInteractionComponent* FindInteractionComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UInteractionComponent>() : nullptr); }

	AActor* GetInteractionActor() const;

	UPROPERTY(BlueprintAssignable)
	FOnInteractionActorChanged OnInteractionActorChanged;

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> InteractionActor;
};
