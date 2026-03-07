// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerHelper.h"

#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizer/Data/DinoCustomizationAppearence.h"

UDinoCustomizerAction* UDinoCustomizerHelper::GetCustomizationInstanceDataFromDatabase(
	UDinoCustomizerDatabase* InDatabase, FGameplayTag Domain, FGameplayTag InstanceTag)
{
	if(IsValid(InDatabase) == false) return nullptr;


	if(UDinoCustomizerDatabaseDomain* DomainData = InDatabase->GetDomainByTag(Domain))
	{
		return DomainData->GetInstanceByTag(InstanceTag);
	}
	return nullptr;
}


FDinoCustomizationAppearance UDinoCustomizerHelper::GenerateMinimalCustomizationAppearanceFromDatabase(UDinoCustomizerDatabase* InDatabase)
{

	FDinoCustomizationAppearance AppearanceData = FDinoCustomizationAppearance();

	if(IsValid(InDatabase) == false) return AppearanceData;

	for(UDinoCustomizerDatabaseDomain* Domain : InDatabase->Domains)
	{
		if(UDinoCustomizerAction* MinimalInstance = Domain->GetMinimalInstance())
		{
			AppearanceData.AddOrUpdateDomainData(Domain->DomainTag, MinimalInstance->InstanceTag);
		}
	}
	
	return AppearanceData;
}


FDinoCustomizationAppearance UDinoCustomizerHelper::GenerateRandomCustomizationAppearanceFromDatabase( UDinoCustomizerDatabase* InDatabase, bool bSelectRandomForEachSubDomainForAllDomains)
{
	
	FDinoCustomizationAppearance AppearanceData = FDinoCustomizationAppearance();

	if(IsValid(InDatabase) == false) return AppearanceData;

	for(UDinoCustomizerDatabaseDomain* Domain : InDatabase->Domains)
	{
		if(UDinoCustomizerAction* RandomInstance = Domain->GetRandomInstance())
		{
			AppearanceData.AddOrUpdateDomainData(Domain->DomainTag, RandomInstance->InstanceTag);
		}
	}
	
	return AppearanceData;
}

FGameplayTag UDinoCustomizerHelper::GetAppearanceDomainInstance(
	const FDinoCustomizationAppearance& CharacterAppearance, FGameplayTag DomainTag)
{

	for(FDinoCustomizationAppearanceDomainData Data :  CharacterAppearance.Domains)
	{
		if(Data.DomainTag.MatchesTagExact(DomainTag))
		{
			return Data.InstanceTag;
		}
	}

	return FGameplayTag::EmptyTag;
}

FGameplayTag UDinoCustomizerHelper::GetAppearanceSubDomainInstance(
	const FDinoCustomizationAppearance& CharacterAppearance, FGameplayTag DomainTag, FGameplayTag SubDomainTag)
{
	for(FDinoCustomizationAppearanceDomainData Data :  CharacterAppearance.Domains)
	{
		if(Data.DomainTag.MatchesTagExact(DomainTag))
		{
				for(FDinoCustomizationAppearanceSubDomainData SubDomain :  Data.SubDomains)
				{
					if(SubDomain.SubDomainTag.MatchesTagExact(SubDomainTag))
					{
						return SubDomain.SubInstanceTag;
					}
				}
			
		}
	}

	return FGameplayTag::EmptyTag;
}
