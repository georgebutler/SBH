#include "SBHPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "SBH/Characters/SBHPlayerCharacter.h"
#include "SBH/UI/SBHUserWidgetHUD.h"

ASBHPlayerController::ASBHPlayerController()
{
	PlayerCharacterWidgetInstance = nullptr;
}

void ASBHPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	check(PlayerCharacterWidget);
	
	if (InPawn->IsA(ASBHPlayerCharacter::StaticClass()))
	{
		if (PlayerCharacterWidgetInstance)
		{
			PlayerCharacterWidgetInstance->RemoveFromParent();
		}
	
		PlayerCharacterWidgetInstance = CreateWidget(GetWorld(), PlayerCharacterWidget);
		PlayerCharacterWidgetInstance->AddToViewport();
	}
}

void ASBHPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	if (PlayerCharacterWidgetInstance)
	{
		PlayerCharacterWidgetInstance->RemoveFromParent();
	}
}
