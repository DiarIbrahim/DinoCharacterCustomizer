// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCharacterCustomizerHelper.h"

#include "DinoCharacterCustomizer/Interfaces/DinoCustomizableCharacterInterface.h"
#include "GameFramework/Character.h"


UDinoCharacterCustomizerAction* UDinoCharacterCustomizerHelper::GetCharacterInstanceDataFromDatabase(
	UDinoCharacterDataBase* InDatabase, FGameplayTag Domain, FGameplayTag InstanceTag)
{
	if(IsValid(InDatabase) == false) return nullptr;

	if(InDatabase->CustomizableDomains.Contains(Domain) == false) return nullptr;

	UDinoCharacterCustomizableDomainData* DomainData = *InDatabase->CustomizableDomains.Find(Domain);

	for(UDinoCharacterCustomizerAction* Instance : DomainData->Instances)
	{
		if(Instance->InstanceTag.MatchesTagExact(InstanceTag))
		{
			return Instance;
		}
	}
	
	return nullptr;
}

TMap<FGameplayTag, UDinoCharacterCustomizerAction*> UDinoCharacterCustomizerHelper::LoadCharacterAppearanceData(
	UDinoCharacterDataBase* InDatabase, const FDinoCharacterAppearance& CharacterAppearance)
{
	TMap<FGameplayTag, UDinoCharacterCustomizerAction*> CharacterInstanceData;

	for(const auto& Pair : CharacterAppearance.GetDomainsAsMap())
	{
		// check if the domain is available in the database
		if(InDatabase->CustomizableDomains.Contains(Pair.Key) == false)  continue;;

		UDinoCharacterCustomizableDomainData* DomainData = *InDatabase->CustomizableDomains.Find(Pair.Key);

		for( UDinoCharacterCustomizerAction* Instance : DomainData->Instances)
		{
			if(Instance->InstanceTag.MatchesTagExact(Pair.Value))
			{
				CharacterInstanceData.Add(Pair.Key, Instance);
			}
		}
	}
	
	return CharacterInstanceData;
}

FDinoCharacterAppearance UDinoCharacterCustomizerHelper::GenerateMinimalCharacterAppearanceFromDatabase(UDinoCharacterDataBase* InDatabase)
{

	FDinoCharacterAppearance AppearanceData = FDinoCharacterAppearance();

	if(IsValid(InDatabase) == false) return AppearanceData;

	for(const auto& Pair : InDatabase->CustomizableDomains)
	{
		if(Pair.Value->Instances.IsEmpty() == false)
		{
			UDinoCharacterCustomizerAction* Instance = Pair.Value->Instances[0];
			AppearanceData.AddOrUpdateDomainData(Pair.Key, Instance->InstanceTag);
		}
	}
	
	return AppearanceData;
}

FDinoCharacterAppearance UDinoCharacterCustomizerHelper::GenerateMinimalCharacterAppearanceFromDatabaseForCharacter(UDinoCharacterDataBase* InDatabase, ACharacter* Character)
{

	FDinoCharacterAppearance AppearanceData = FDinoCharacterAppearance();

	if(IsValid(InDatabase) == false || IsValid(Character) == false || Character->Implements<UDinoCustomizableCharacterInterface>() == false) return AppearanceData;

	IDinoCustomizableCharacterInterface* Interface = Cast<IDinoCustomizableCharacterInterface>(Character);
	
	TArray<FGameplayTag> CharacterDomains;
	Interface->GetCustomizableDomains().GetKeys(CharacterDomains);
	

	for(const auto& Pair : InDatabase->CustomizableDomains)
	{
		// ignore any domain that is not required by the character
		if(CharacterDomains.Contains(Pair.Key) == false) continue;
		
			if(Pair.Value->Instances.IsEmpty() == false)
			{
				UDinoCharacterCustomizerAction* Instance  = Pair.Value->Instances[0];
				AppearanceData.AddOrUpdateDomainData(Pair.Key, Instance->InstanceTag);
			}
	}
	
	
	return AppearanceData;
}

FDinoCharacterAppearance UDinoCharacterCustomizerHelper::GenerateRandomCharacterAppearanceFromDatabase( UDinoCharacterDataBase* InDatabase)
{
	
	FDinoCharacterAppearance AppearanceData = FDinoCharacterAppearance();

	if(IsValid(InDatabase) == false) return AppearanceData;

	for(const auto& Pair : InDatabase->CustomizableDomains)
	{
		if(Pair.Value->Instances.IsEmpty() == false)
		{
			UDinoCharacterCustomizerAction* Instance  = Pair.Value->Instances[FMath::RandRange(0,  Pair.Value->Instances.Num()-1)];
			AppearanceData.AddOrUpdateDomainData(Pair.Key, Instance->InstanceTag);
		}
	}
	
	
	return AppearanceData;
}

FDinoCharacterAppearance UDinoCharacterCustomizerHelper::GenerateRandomCharacterAppearanceFromDatabaseForCharacter( UDinoCharacterDataBase* InDatabase, ACharacter* Character)
{
	
	FDinoCharacterAppearance AppearanceData = FDinoCharacterAppearance();

	if(IsValid(InDatabase) == false || IsValid(Character) == false || Character->Implements<UDinoCustomizableCharacterInterface>() == false) return AppearanceData;

	IDinoCustomizableCharacterInterface* Interface = Cast<IDinoCustomizableCharacterInterface>(Character);
	
	TArray<FGameplayTag> CharacterDomains;
	Interface->GetCustomizableDomains().GetKeys(CharacterDomains);
	

	for(const auto& Pair : InDatabase->CustomizableDomains)
	{
		// ignore any domain that is not required by the character
		if(CharacterDomains.Contains(Pair.Key) == false) continue;
			if(Pair.Value->Instances.IsEmpty() == false)
			{
				UDinoCharacterCustomizerAction* Instance = Pair.Value->Instances[FMath::RandRange(0,  Pair.Value->Instances.Num()-1)];
				AppearanceData.AddOrUpdateDomainData(Pair.Key, Instance->InstanceTag);
			}
		
	}
	
	
	return AppearanceData;
}

FGameplayTag UDinoCharacterCustomizerHelper::GetCharacterAppearanceDomainInstance(
	const FDinoCharacterAppearance& CharacterAppearance, FGameplayTag DomainTag)
{
	TMap<FGameplayTag,FGameplayTag> Map = CharacterAppearance.GetDomainsAsMap();
	if(Map.Contains(DomainTag))
	{
		return Map[DomainTag];
	}
	return FGameplayTag::EmptyTag;
}
