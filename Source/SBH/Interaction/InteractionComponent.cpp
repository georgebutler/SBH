#include "InteractionComponent.h"

UInteractionComponent::UInteractionComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	InteractionActor = nullptr;
}

AActor* UInteractionComponent::GetInteractionActor() const
{
	return InteractionActor;
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UWorld* World = GetWorld();
	AActor* Owner = GetOwner();
	
	if (World && Owner)
	{
		FVector Start, End;
		FRotator EyeRotation;
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(Owner);

		Owner->GetActorEyesViewPoint(Start, EyeRotation);
		End = Start + EyeRotation.Vector() * 400.f;
		World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

		// DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor(255, 0, 0), false, 1, 1, 3.f);
		
		AActor* HitActor = HitResult.GetActor();
		
		if (InteractionActor != HitActor)
		{
			OnInteractionActorChanged.Broadcast(InteractionActor, HitActor);
			InteractionActor = HitActor;
		}
	}
}
