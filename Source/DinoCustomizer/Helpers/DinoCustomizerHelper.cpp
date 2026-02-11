// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerHelper.h"

#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizer/Data/DinoCustomizationAppearence.h"
#include "DinoCustomizer/Data/DinoCustomizationDataBase.h"

UDinoCustomizerAction* UDinoCustomizerHelper::GetCustomizationInstanceDataFromDatabase(
	UDinoCustomizationDataBase* InDatabase, FGameplayTag Domain, FGameplayTag InstanceTag)
{
	if(IsValid(InDatabase) == false) return nullptr;

	if(InDatabase->CustomizableDomains.Contains(Domain) == false) return nullptr;

	UDinoCustomizableDomainData* DomainData = *InDatabase->CustomizableDomains.Find(Domain);

	for(UDinoCustomizerAction* Instance : DomainData->Instances)
	{
		if(Instance->InstanceTag.MatchesTagExact(InstanceTag))
		{
			return Instance;
		}
	}
	
	return nullptr;
}

TMap<FGameplayTag, UDinoCustomizerAction*> UDinoCustomizerHelper::LoadCharacterAppearanceData(
	UDinoCustomizationDataBase* InDatabase, const FDinoCustomizationAppearance& CharacterAppearance)
{
	TMap<FGameplayTag, UDinoCustomizerAction*> CharacterInstanceData;

	for(const auto& Pair : CharacterAppearance.GetDomainsAsMap())
	{
		// check if the domain is available in the database
		if(InDatabase->CustomizableDomains.Contains(Pair.Key) == false)  continue;;

		UDinoCustomizableDomainData* DomainData = *InDatabase->CustomizableDomains.Find(Pair.Key);

		for( UDinoCustomizerAction* Instance : DomainData->Instances)
		{
			if(Instance->InstanceTag.MatchesTagExact(Pair.Value))
			{
				CharacterInstanceData.Add(Pair.Key, Instance);
			}
		}
	}
	
	return CharacterInstanceData;
}

FDinoCustomizationAppearance UDinoCustomizerHelper::GenerateMinimalCustomizationAppearanceFromDatabase(UDinoCustomizationDataBase* InDatabase)
{

	FDinoCustomizationAppearance AppearanceData = FDinoCustomizationAppearance();

	if(IsValid(InDatabase) == false) return AppearanceData;

	for(const auto& Pair : InDatabase->CustomizableDomains)
	{
		if(Pair.Value->Instances.IsEmpty() == false)
		{
			UDinoCustomizerAction* Instance = Pair.Value->Instances[0];
			AppearanceData.AddOrUpdateDomainData(Pair.Key, Instance->InstanceTag);
		}
	}
	
	return AppearanceData;
}


FDinoCustomizationAppearance UDinoCustomizerHelper::GenerateRandomCustomizationAppearanceFromDatabase( UDinoCustomizationDataBase* InDatabase)
{
	
	FDinoCustomizationAppearance AppearanceData = FDinoCustomizationAppearance();

	if(IsValid(InDatabase) == false) return AppearanceData;

	for(const auto& Pair : InDatabase->CustomizableDomains)
	{
		if(Pair.Value->Instances.IsEmpty() == false)
		{
			UDinoCustomizerAction* Instance  = Pair.Value->Instances[FMath::RandRange(0,  Pair.Value->Instances.Num()-1)];
			AppearanceData.AddOrUpdateDomainData(Pair.Key, Instance->InstanceTag);
		}
	}
	
	
	return AppearanceData;
}

FGameplayTag UDinoCustomizerHelper::GetCharacterAppearanceDomainInstance(
	const FDinoCustomizationAppearance& CharacterAppearance, FGameplayTag DomainTag)
{
	TMap<FGameplayTag,FGameplayTag> Map = CharacterAppearance.GetDomainsAsMap();
	if(Map.Contains(DomainTag))
	{
		return Map[DomainTag];
	}
	return FGameplayTag::EmptyTag;
}
