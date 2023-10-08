#pragma once

#include "CoreMinimal.h"
#include "SBH/Equipment/EquipmentInstance.h"
#include "WeaponInstance.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UENUM(BlueprintType)
enum EWeaponFiringMode
{
	SemiAutomatic,
	Automatic
};

UCLASS(BlueprintType, Blueprintable)
class SBH_API AWeaponInstance : public AEquipmentInstance
{
	GENERATED_BODY()

public:
	AWeaponInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float FirePrimaryDelay = 0.2f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float FirePrimaryRange = 10000.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float FirePrimaryDamage = 15.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UDamageType> PrimaryDamageType;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TEnumAsByte<EWeaponFiringMode> FiringMode;

	virtual void Equip_Implementation(ACharacter* Character) override;
	virtual void Unequip_Implementation() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BeginFirePrimary(const FInputActionValue& Input);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndFirePrimary(const FInputActionValue& Input);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BeginFireSecondary(const FInputActionValue& Input);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndFireSecondary(const FInputActionValue& Input);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Reload(const FInputActionValue& Input);

private:
	FTimerHandle FirePrimaryTimerHandle;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PrimaryFireAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SecondaryFireAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ReloadAction;

	UFUNCTION()
	void FirePrimary();
};