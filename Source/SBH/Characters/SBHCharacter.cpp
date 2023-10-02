#include "SBHCharacter.h"

#include "Components/CapsuleComponent.h"
#include "SBH/Stats/StatsComponent.h"

static FName GName_SBHCharacterCollisionProfile_Capsule(TEXT("SBHPawnCapsule"));
static FName GName_SBHCharacterCollisionProfile_Mesh(TEXT("SBHPawnMesh"));

ASBHCharacter::ASBHCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(55.0f, 96.0f);
	CapsuleComp->SetCollisionProfileName(GName_SBHCharacterCollisionProfile_Capsule);

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
}

void ASBHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UStatsComponent* ASBHCharacter::GetStatsComponent() const
{
	return StatsComponent;
}