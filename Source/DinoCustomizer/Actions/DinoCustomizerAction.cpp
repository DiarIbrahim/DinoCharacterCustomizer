// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerAction.h"
#include "DinoCustomizer/Actors/DinoCustomizerStudio.h"


void UDinoCustomizerAction::InitAction(FDinoCustomizerActionActivationData ActivationData)
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


void UDinoCustomizerAction::OnActionStarted_Implementation(const FDinoCustomizerActionActivationData& ActivationData)
{
}


bool UDinoCustomizerAction::ValidateAction_Implementation() const
{
	return true;
}

void UDinoCustomizerAction::CommitAction()
{
	if(IsValid(CurrentActivationData.OwningCustomizerPawn) == false ) return;

	if(InstanceTag.IsValid() == false) return;

	CurrentActivationData.OwningCustomizerPawn->CommitCustomizationActionOnDomain(CurrentActivationData.TargetDomainTag, InstanceTag);
	
}


void UDinoCustomizerAction::EndAction()
{

	OnActionEnded();

	// notify the owning pawn that we are done !
}

void UDinoCustomizerAction::OnActionEnded_Implementation()
{
}
