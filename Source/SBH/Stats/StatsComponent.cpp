#include "StatsComponent.h"

UStatsComponent::UStatsComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	MaxHealth = 100.0f;
	Health = MaxHealth;
	bIsAlive = true;
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UStatsComponent::HandleAnyDamage);
	
	OnHealthChanged.Broadcast(Health, Health);
	OnMaxHealthChanged.Broadcast(MaxHealth, MaxHealth);
}

void UStatsComponent::HandleAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (bIsAlive)
	{
		const float OldHealth = Health;
		Health -= Damage;
		
		UE_LOG(LogTemp, Warning, TEXT("Health Changed: %f -> %f"), OldHealth, Health);
	
		if (Health <= 0.0f)
		{
			Health = 0.0f;
			bIsAlive = false;
			OnHealthZero.Broadcast();
		}

		OnHealthChanged.Broadcast(OldHealth, Health);	
	}
}

