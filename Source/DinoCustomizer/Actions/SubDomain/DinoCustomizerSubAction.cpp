// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerSubAction.h"


void UDinoCustomizerSubAction::InitAction(UDinoCustomizerAction* OwnerAction, UObject* TargetObject)
{
	OnActionStarted(OwnerAction, TargetObject);
}

void UDinoCustomizerSubAction::OnActionStarted_Implementation(UDinoCustomizerAction* OwnerAction, UObject* TargetObject)
{
}
