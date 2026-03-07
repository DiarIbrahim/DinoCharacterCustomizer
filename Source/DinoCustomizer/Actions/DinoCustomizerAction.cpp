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

	ApplyDefaultSubAction();
}


void UDinoCustomizerAction::ApplyDefaultSubAction()
{

	
	// first we apply sub actions we received when this action started

	/*
	for(const auto& Pair : CurrentActivationData.ActiveSubDomains)
	{
		if(SubDomains.Contains(Pair.Key) == false) continue;

		FDinoCustomizerSubDomainContainer SubDomainContainer = SubDomains[Pair.Key];

		if(UDinoCustomizerSubAction* SubAction = SubDomainContainer.FindSubDomainInstance(Pair.Value))
		{
			ApplySubActionOnSubDomain(SubAction, Pair.Key);
		}
		
	}
	*/
	

	/*for(const auto& Pair : SubDomains)
	{
		// No default for this sub domain since we already have an active received during the activation
		if(CurrentActivationData.ActiveSubDomains.Contains(Pair.Key)) continue;
		
		if(Pair.Value.bApplyFirstSubAction)
		{
			if(Pair.Value.SubActions.IsEmpty() == false)
			{
				ApplySubActionOnSubDomain(Pair.Value.SubActions[0], Pair.Key);
			}
		}
	}*/
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

	CurrentActivationData.OwningCustomizerPawn->CommitCustomizationActionOnDomain(CurrentActivationData.TargetDomainTag, InstanceTag, CurrentActiveSubDomains);
	
}


void UDinoCustomizerAction::EndAction()
{

	OnActionEnded();

	// notify the owning pawn that we are done !
}

void UDinoCustomizerAction::OnActionEnded_Implementation()
{
}

void UDinoCustomizerAction::ApplySubActionOnSubDomain(UDinoCustomizerSubAction* SubAction, const FGameplayTag& SubDomainTag)
{
	if(IsValid(SubAction))
	{
		SubAction->InitAction(this, CurrentActivationData.TargetDomainObject);

		// add or update
		CurrentActiveSubDomains.Add(SubDomainTag, SubAction->SubInstanceTag);
	}
}

UDinoCustomizerSubDomain* UDinoCustomizerAction::AddSubDomain()
{

	UDinoCustomizerSubDomain* NewSubDomain = NewObject<UDinoCustomizerSubDomain>(this, GetNewSubDomainName());
	SubDomains.Add(NewSubDomain);

	return NewSubDomain;
	
}

UDinoCustomizerSubDomain* UDinoCustomizerAction::DuplicateSubDomain(UDinoCustomizerSubDomain* SubDomainToReplicate)
{
	UDinoCustomizerSubDomain* NewSubDomain = DuplicateObject<UDinoCustomizerSubDomain>(SubDomainToReplicate,this, GetNewSubDomainName());
	SubDomains.Add(NewSubDomain);

	return NewSubDomain;
}

bool UDinoCustomizerAction::RemoveSubDomain(UDinoCustomizerSubDomain* SubDomainToRemove)
{
	if(SubDomains.Contains(SubDomainToRemove))
	{
		SubDomains.Remove(SubDomainToRemove);
		return true;
	}
	return false;
}

FName UDinoCustomizerAction::GetNewSubDomainName()
{
	int32 NumToUse = -1;
	for(UDinoCustomizerSubDomain* SubDomain : SubDomains)
	{
		FString Name = SubDomain->GetName();
		FString L;
		FString R;
	
		Name.Split("_", &L,&R,ESearchCase::IgnoreCase,ESearchDir::FromEnd);

		int32 EndingNum = FCString::Atoi(*R);
		if(EndingNum > NumToUse)
		{
			NumToUse = EndingNum;
		}

	}

	return FName(FString("SubDomain_").Append(FString::FromInt(++NumToUse)));

}
