// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerSubDomain.h"
#include "DinoCustomizerSubAction.h"
#include "DinoCustomizer/Helpers/DinoCustomizerHelper.h"

UDinoCustomizerSubAction* UDinoCustomizerSubDomain::AddSubInstances(TSubclassOf<UDinoCustomizerSubAction> SubInstanceClass)
{
	FName NewSubInstanceName = FName("");
	GetNewInstanceName(NewSubInstanceName);

	UDinoCustomizerSubAction* NewSubInstance = NewObject<UDinoCustomizerSubAction>(this, SubInstanceClass, NewSubInstanceName);
	NewSubInstance->SubInstanceTag = GetNextSubInstanceTag();
	SubInstances.Add(NewSubInstance);

	return NewSubInstance;
}

UDinoCustomizerSubAction* UDinoCustomizerSubDomain::DuplicateSubInstances(UDinoCustomizerSubAction* SourceSubInstance)
{
	FName NewSubInstanceName = FName("");
	GetNewInstanceName(NewSubInstanceName);

	UDinoCustomizerSubAction* NewSubInstance = DuplicateObject<UDinoCustomizerSubAction>(SourceSubInstance, this, NewSubInstanceName);
	NewSubInstance->SubInstanceTag = GetNextSubInstanceTag();
	SubInstances.Add(NewSubInstance);

	return NewSubInstance;
}

bool UDinoCustomizerSubDomain::RemoveSubInstances(UDinoCustomizerSubAction* SubInstanceToRemove)
{
	if(SubInstances.Contains(SubInstanceToRemove))
	{
		SubInstances.Remove(SubInstanceToRemove);
		return true;
	}

	return false;
}

UDinoCustomizerSubAction* UDinoCustomizerSubDomain::GetMinimalSubInstance()
{
	if(SubInstances.IsEmpty()) return nullptr;
	return SubInstances[0];
}

UDinoCustomizerSubAction* UDinoCustomizerSubDomain::GetRandomSubInstance()
{
	if(SubInstances.IsEmpty()) return nullptr;
	if(SubInstances.Num() == 1) return SubInstances[0];

	return SubInstances[FMath::RandRange(0, SubInstances.Num() - 1)];
}

bool UDinoCustomizerSubDomain::MoveSubInstanceOrderUp(UDinoCustomizerSubAction* SubInstance)
{
	int32 Index = SubInstances.Find(SubInstance);

	if (Index != INDEX_NONE && Index > 0)
	{
		SubInstances.Swap(Index, Index - 1);
		return true;
	}
	return false;
}

bool UDinoCustomizerSubDomain::MoveSubInstanceOrderDown(UDinoCustomizerSubAction* SubInstance)
{
	int32 Index = SubInstances.Find(SubInstance);

	if (Index != INDEX_NONE && Index < SubInstances.Num() - 1)
	{
		SubInstances.Swap(Index, Index + 1);
		return true;
	}

	return false;
}

void UDinoCustomizerSubDomain::GetNewInstanceName(FName& NewActionName)
{

	int32 NumToUse = -1;
	for(UDinoCustomizerSubAction* Instance : SubInstances)
	{
		FString Name = Instance->GetName();
		FString L;
		FString R;
	
		Name.Split("_", &L,&R,ESearchCase::IgnoreCase,ESearchDir::FromEnd);

		int32 EndingNum = FCString::Atoi(*R);
		if(EndingNum > NumToUse)
		{
			NumToUse = EndingNum;
		}

	}

	NewActionName = FName(FString("SubInstance_").Append(FString::FromInt(++NumToUse)));
	
}

FGameplayTag UDinoCustomizerSubDomain::GetNextSubInstanceTag()
{
	FGameplayTagContainer AlreadyUsedTags;

	for(UDinoCustomizerSubAction* Inst : SubInstances)
	{
		if (IsValid(Inst))
		{
			AlreadyUsedTags.AddTag(Inst->SubInstanceTag);
		}
	}

	return UDinoCustomizerHelper::GetNextUnUsedCustomizableSubInstanceTag(AlreadyUsedTags);
}
