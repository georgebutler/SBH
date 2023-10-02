#include "SBHUserWidgetHUD.h"

#include "Kismet/GameplayStatics.h"
#include "SBH/Characters/SBHPlayerCharacter.h"

void USBHUserWidgetHUD::NativeConstruct()
{
	PlayerCharacterInstance = CastChecked<ASBHPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	Super::NativeConstruct();
}
