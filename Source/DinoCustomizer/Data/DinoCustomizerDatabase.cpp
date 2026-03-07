// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerDatabase.h"

#include "DinoCustomizer/Actions/DinoCustomizerAction.h"


UDinoCustomizerDatabaseDomain::UDinoCustomizerDatabaseDomain()
{
	DomainId = FGuid::NewGuid();
}

UDinoCustomizerAction* UDinoCustomizerDatabaseDomain::AddNewInstance(TSubclassOf<UDinoCustomizerAction> ActionClass)
{

	if(IsValid(ActionClass) == false) return nullptr;
	
	FName NewActionName;
	GetNewInstanceName(NewActionName);
	UDinoCustomizerAction* NewAction = NewObject<UDinoCustomizerAction>(this,ActionClass, NewActionName);

	Instances.Add(NewAction);

	return NewAction;
}

void UDinoCustomizerDatabaseDomain::GetNewInstanceName(FName& NewActionName)
{
	int32 NumToUse = -1;
	for(UDinoCustomizerAction* Action : Instances)
	{
		FString Name = Action->GetName();
		FString L;
		FString R;
		
		Name.Split("_", &L,&R,ESearchCase::IgnoreCase,ESearchDir::FromEnd);

		int32 EndingNum = FCString::Atoi(*R);
		if(EndingNum > NumToUse)
		{
			NumToUse = EndingNum;
		}

	}

	NewActionName = FName(FString("DomainInstance_").Append(FString::FromInt(++NumToUse)));
}

UDinoCustomizerAction* UDinoCustomizerDatabaseDomain::DuplicateInstance(UDinoCustomizerAction* Instance)
{
	FName NewActionName;
	GetNewInstanceName(NewActionName);
	UDinoCustomizerAction* NewAction = DuplicateObject<UDinoCustomizerAction>(Instance, this ,NewActionName);
	NewAction->InstanceTag = FGameplayTag::EmptyTag;
	Instances.Add(NewAction);

	return NewAction;

}

bool UDinoCustomizerDatabaseDomain::RemoveInstance(UDinoCustomizerAction* Instance)
{
	
		Instances.Remove(Instance);
		return true;
}

UDinoCustomizerAction* UDinoCustomizerDatabaseDomain::GetInstanceByTag(FGameplayTag InInstanceTag)
{
	for(UDinoCustomizerAction* Instance : Instances)
	{
		if(Instance->InstanceTag.MatchesTagExact(InInstanceTag))
		{
			return Instance;
		}
	}

	return nullptr;
}

UDinoCustomizerAction* UDinoCustomizerDatabaseDomain::GetRandomInstance()
{
	if(Instances.IsEmpty()) return nullptr;

	if(Instances.Num() == 1) return Instances[0];
	
	int32 RandomInstance = FMath::RandRange(0, Instances.Num() - 1);
	return Instances[RandomInstance];
}

UDinoCustomizerAction* UDinoCustomizerDatabaseDomain::GetMinimalInstance()
{
	if(Instances.IsEmpty()) return nullptr;
	return Instances[0];
}


/////////////////////////////////
///  ------  DATABASE  ------////
/////////////////////////////////

UDinoCustomizerDatabaseDomain* UDinoCustomizerDatabase::AddNewDatabaseDomain()
{

	int32 NumToUse = 0;
	for(UDinoCustomizerDatabaseDomain* Domain : Domains)
	{
		FString Name = Domain->GetName();
		FString L;
		FString R;
		
		Name.Split("_", &L,&R,ESearchCase::IgnoreCase,ESearchDir::FromEnd);

		int32 EndingNum = FCString::Atoi(*R);
		if(EndingNum > NumToUse)
		{
			NumToUse = EndingNum;
		}
		
	}

	FName NewDomainName = FName(FString("Domain_").Append(FString::FromInt(++NumToUse)));
	
	UDinoCustomizerDatabaseDomain* NewDomain = NewObject<UDinoCustomizerDatabaseDomain>(this, NewDomainName);
	Domains.Add(NewDomain);

	return NewDomain;
}

bool UDinoCustomizerDatabase::RemoveDatabaseDomain(UDinoCustomizerDatabaseDomain* Domain)
{
	if(Domains.Contains(Domain))
	{
		Domains.Remove(Domain);
		return true;
	}
	return false;
}

bool UDinoCustomizerDatabase::MoveDomainOrderUp(UDinoCustomizerDatabaseDomain* Domain)
{
	int32 Index = Domains.Find(Domain);

	if (Index != INDEX_NONE && Index > 0)
	{
		Domains.Swap(Index, Index - 1);
		return true;
	}
		return false;
}

bool UDinoCustomizerDatabase::MoveDomainOrderDown(UDinoCustomizerDatabaseDomain* Domain)
{
	int32 Index = Domains.Find(Domain);

	if (Index != INDEX_NONE && Index < Domains.Num() - 1)
	{
		Domains.Swap(Index, Index + 1);
		return true;
	}

	return false;
}

UDinoCustomizerDatabaseDomain* UDinoCustomizerDatabase::GetDomainByTag(FGameplayTag InDomainTag)
{
	for(UDinoCustomizerDatabaseDomain* Domain : Domains)
	{
		if(Domain->DomainTag.MatchesTagExact(InDomainTag))
		{
			return Domain;
		}
	}

	return nullptr;
}
