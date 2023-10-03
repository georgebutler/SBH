#pragma once

#include "CoreMinimal.h"
#include "SBHCharacter.h"
#include "SBHPlayerCharacter.generated.h"

class UEquipmentManagerComponent;
class UInteractionComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRespawned, ASBHCharacter*, NewCharacter);

UCLASS(Abstract, Blueprintable)
class SBH_API ASBHPlayerCharacter : public ASBHCharacter
{
	GENERATED_BODY()

public:
	ASBHPlayerCharacter();

	UPROPERTY(BlueprintAssignable)
	FOnDied OnDied;

	UPROPERTY(BlueprintAssignable)
	FOnRespawned OnRespawned;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void DestroyPlayerInputComponent() override;
	virtual void FellOutOfWorld(const UDamageType& DmgType) override;
	
	void Move(const FInputActionValue& Input);
	void Look(const FInputActionValue& Input);
	void Interact(const FInputActionValue& Input);

private:
	UPROPERTY()
	FTimerHandle TimerHandleRespawn;

	UFUNCTION()
	void OnCharacterDied();
	
	UFUNCTION()
	void OnCharacterRespawned();
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Character", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASBHPlayerCharacter> PlayerCharacter;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Character|Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Character|Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Character|Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Character|Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player Character|Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInteractionComponent> InteractionComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipmentManagerComponent> EquipmentManagerComponent;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> FirstPersonArms;
};