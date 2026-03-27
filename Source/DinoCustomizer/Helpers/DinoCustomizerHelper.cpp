// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerHelper.h"

#include "GameplayTagsManager.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizer/Data/DinoCustomizationAppearence.h"
#include "DinoCustomizer/Tags/DinoCustomizerTags.h"

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
			FDinoCustomizationAppearanceDomainData& DomainData = AppearanceData.GetDomainData(Domain->DomainTag);
			DomainData.InstanceTag = MinimalInstance->InstanceTag;
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
			TMap<FGameplayTag, FGameplayTag> SubDomains;
			for(UDinoCustomizerSubDomain* SubDomain : RandomInstance->SubDomains)
			{
				if(UDinoCustomizerSubAction* RandomSubInstance = SubDomain->GetRandomSubInstance())
				{
					SubDomains.Add(SubDomain->SubDomainTag, RandomSubInstance->SubInstanceTag);
				}
			}
			FDinoCustomizationAppearanceDomainData& DomainData = AppearanceData.GetDomainData(Domain->DomainTag);
			DomainData.InstanceTag = RandomInstance->InstanceTag;
			DomainData.SetSubDomainsFromMap(SubDomains);
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

FGameplayTag UDinoCustomizerHelper::GetNextUnUsedCustomizableInstanceTag(const FGameplayTagContainer& UsedTags)
{

	FGameplayTagContainer CustomizableInstanceTags =  UGameplayTagsManager::Get().RequestGameplayTagChildren(DinoCustomizationTags::CustomizableInstance_Root);

	for(FGameplayTag Tag : CustomizableInstanceTags)
	{
		if(UsedTags.HasTagExact(Tag) == false)
		{
			return Tag;
		}
	}

	return FGameplayTag::EmptyTag;
}

FGameplayTag UDinoCustomizerHelper::GetNextUnUsedCustomizableSubInstanceTag(const FGameplayTagContainer& UsedTags)
{
	FGameplayTagContainer CustomizableInstanceTags =  UGameplayTagsManager::Get().RequestGameplayTagChildren(DinoCustomizationTags::CustomizableSubInstance_Root);

	for(FGameplayTag Tag : CustomizableInstanceTags)
	{
		if(UsedTags.HasTagExact(Tag) == false)
		{
			return Tag;
		}
	}

	return FGameplayTag::EmptyTag;
}

void UDinoCustomizerHelper::DebugPrintAppearance(const FDinoCustomizationAppearance& Appearance, float Duration,FLinearColor Color)
{
	
	FString Message = "---------- Appearance Data -------- \n";
	for(FDinoCustomizationAppearanceDomainData Data :  Appearance.Domains)
	{
		Message += " - DomainTag: " + Data.DomainTag.ToString() + "  -- Instance : " + Data.InstanceTag.ToString() + "\n";
		for(FDinoCustomizationAppearanceSubDomainData SubDomain :  Data.SubDomains)
		{
			Message += " ----------------- SubDomain: " + SubDomain.SubDomainTag.ToString() +  "   -- Sub Instance "  + SubDomain.SubInstanceTag.ToString() + "\n";
		}
		Message += "\n";
		
	}
	Message += "\n ---------- END  -------- ";
	
	GEngine->AddOnScreenDebugMessage(-1,Duration,Color.ToFColor(true), Message);
}



