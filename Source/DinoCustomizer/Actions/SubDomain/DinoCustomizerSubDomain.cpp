// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerSubDomain.h"
#include "DinoCustomizerSubAction.h"

UDinoCustomizerSubAction* UDinoCustomizerSubDomain::AddSubInstances(TSubclassOf<UDinoCustomizerSubAction> SubInstanceClass)
{
	FName NewSubInstanceName = FName("");
	GetNewInstanceName(NewSubInstanceName);

	UDinoCustomizerSubAction* NewSubInstance = NewObject<UDinoCustomizerSubAction>(this, SubInstanceClass, NewSubInstanceName);
	SubInstances.Add(NewSubInstance);

	return NewSubInstance;
}

UDinoCustomizerSubAction* UDinoCustomizerSubDomain::DuplicateSubInstances(UDinoCustomizerSubAction* SourceSubInstance)
{
	FName NewSubInstanceName = FName("");
	GetNewInstanceName(NewSubInstanceName);

	UDinoCustomizerSubAction* NewSubInstance = DuplicateObject<UDinoCustomizerSubAction>(SourceSubInstance, this, NewSubInstanceName);
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
