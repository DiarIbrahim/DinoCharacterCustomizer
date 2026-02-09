// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCharacterCustomizerAction.h"

#include "DinoCharacterCustomizer/Actors/DinoCharacterCustomizerPawn.h"


void UDinoCharacterCustomizerAction::InitAction(FDinoCharacterCustomizerActionActivationData ActivationData)
{
	if(IsValid(ActivationData.TargetActor) == false || ActivationData.TargetDomainTag.IsValid() == false)
	{
		EndAction();
		return;
	}

	CurrentActivationData = ActivationData;

	if(ValidateAction() == false)
	{
		EndAction();
		return;
	}

	OnActionStarted(CurrentActivationData);
	
}


void UDinoCharacterCustomizerAction::OnActionStarted_Implementation(const FDinoCharacterCustomizerActionActivationData& ActivationData)
{
}


bool UDinoCharacterCustomizerAction::ValidateAction_Implementation() const
{
	return true;
}

void UDinoCharacterCustomizerAction::CommitAction()
{
	if(IsValid(CurrentActivationData.OwningCustomizerPawn) == false ) return;

	if(InstanceTag.IsValid() == false) return;

	CurrentActivationData.OwningCustomizerPawn->CommitCustomizationActionOnDomain(CurrentActivationData.TargetDomainTag, InstanceTag);
	
}


void UDinoCharacterCustomizerAction::EndAction()
{

	OnActionEnded();

	// notify the owning pawn that we are done !
}

void UDinoCharacterCustomizerAction::OnActionEnded_Implementation()
{
}
