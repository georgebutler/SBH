﻿#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMaxHealthChanged, float, OldMaxHealth, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, OldHealth, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthZero);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SBH_API UStatsComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UStatsComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure)
	static UStatsComponent* FindStatsComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UStatsComponent>() : nullptr); }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, meta = (ClampMin = 0.1))
	float MaxHealth;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, SaveGame)
	bool bIsAlive;

	UPROPERTY(BlueprintAssignable)
	FOnMaxHealthChanged OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthZero OnHealthZero;
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void HandleAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
