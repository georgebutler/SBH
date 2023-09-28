#include "SBHCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SBH/Stats/StatsComponent.h"

static FName GName_SBHharacterCollisionProfile_Capsule(TEXT("SBHPawnCapsule"));
static FName GName_SBHCharacterCollisionProfile_Mesh(TEXT("SBHPawnMesh"));

ASBHCharacter::ASBHCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(55.0f, 96.0f);
	CapsuleComp->SetCollisionProfileName(GName_SBHharacterCollisionProfile_Capsule);

	USkeletalMeshComponent* MeshComp = GetMesh();
	check(MeshComp);
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	MeshComp->SetRelativeLocation(FVector(0, 0, -90.0f));
	MeshComp->SetCollisionProfileName(GName_SBHCharacterCollisionProfile_Mesh);

	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));
}

void ASBHCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(StatsComponent);
	StatsComponent->OnHealthZero.AddDynamic(this, &ASBHCharacter::OnHealthZero);
}

void ASBHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASBHCharacter::OnHealthZero()
{
	if (Controller)
	{
		Controller->SetIgnoreMoveInput(true);
	}

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	check(MovementComponent);
	MovementComponent->StopMovementImmediately();
	MovementComponent->DisableMovement();
}

