// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Net/Serialization/FastArraySerializer.h"

#include "DinoCustomizationAppearence.generated.h"


/*
 * a sub domain is a customization to a domain instance
 *
 *	e.g.
 *		A domain can be UpperBody
 *		The Instance of that domain can be a Jacket that is applied to the upper body domain
 *		A sub domain is the customization that we want to do that specific instance
 *		like a material change, that can be and will only apply to that instance
 */

USTRUCT(BlueprintType)
struct  FDinoCustomizationAppearanceSubDomainData : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FDinoCustomizationAppearanceSubDomainData(){}
	FDinoCustomizationAppearanceSubDomainData(FGameplayTag InSubDomainTag, FGameplayTag InSubInstanceTag):SubDomainTag(InSubDomainTag), SubInstanceTag(InSubInstanceTag){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag SubDomainTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag SubInstanceTag;
	
	
};



/*
 *  a Domain is any customizable part of the character like Hand, upperBody, lowerBody and so on
 *  an Instance is an instance or a change that can be applied to the domain, e.g. like a hair style that can be applied to hair domain
 */

USTRUCT(BlueprintType)
struct  FDinoCustomizationAppearanceDomainData : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FDinoCustomizationAppearanceDomainData(){}
	FDinoCustomizationAppearanceDomainData(FGameplayTag InDomainTag, FGameplayTag InInstanceTag):DomainTag(InDomainTag), InstanceTag(InInstanceTag){}
	FDinoCustomizationAppearanceDomainData(FGameplayTag InDomainTag, FGameplayTag InInstanceTag, TMap<FGameplayTag, FGameplayTag> InSubDomains):DomainTag(InDomainTag), InstanceTag(InInstanceTag)
	{
		for(const auto& Pair : InSubDomains)
		{
			SubDomains.Add(FDinoCustomizationAppearanceSubDomainData(Pair.Key, Pair.Value));
		}
	}


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag DomainTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag InstanceTag;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDinoCustomizationAppearanceSubDomainData> SubDomains;

	bool AddOrUpdateSubDomain(FGameplayTag InSubDomainTag, FGameplayTag InSubInstanceTag)
	{
		if(InSubDomainTag.IsValid() == false || InSubInstanceTag.IsValid() == false) return false;
		
		for (FDinoCustomizationAppearanceSubDomainData& SubDomain : SubDomains)
		{
			if(SubDomain.SubDomainTag == InSubDomainTag)
			{
				SubDomain.SubInstanceTag = InSubInstanceTag;
				return true;
			}
		}
		
		SubDomains.Add(FDinoCustomizationAppearanceSubDomainData(InSubDomainTag, InSubInstanceTag));
		return true;
			
	}

	
	TMap<FGameplayTag, FGameplayTag> GetSubDomainsAsMap() const
	{
		TMap<FGameplayTag, FGameplayTag> SubDomainsMap;
		for(const FDinoCustomizationAppearanceSubDomainData& SubDomain : SubDomains)
		{
			SubDomainsMap.Add(SubDomain.SubDomainTag, SubDomain.SubInstanceTag);
		}

		return SubDomainsMap;
	}
	
};


/*
 *		a light weight data that is representing the character's Appearance
 *		good to be used to store or transfer over network
 */
USTRUCT(BlueprintType)
struct FDinoCustomizationAppearance : public FFastArraySerializer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDinoCustomizationAppearanceDomainData> Domains;
	
	bool AddOrUpdateDomainData(FGameplayTag DomainTag, FGameplayTag InstanceTag, TMap<FGameplayTag,FGameplayTag> SubDomains = {})
	{
		if(DomainTag.IsValid() == false) return false;
		
		for(FDinoCustomizationAppearanceDomainData& Data : Domains)
		{
			if(Data.DomainTag.MatchesTagExact(DomainTag))
			{
				Data.InstanceTag = InstanceTag;

				for(const auto& Pair : SubDomains)
				{
					Data.AddOrUpdateSubDomain(Pair.Key, Pair.Value);
				}
				
				return true;
			}
		}

		// the domain is not there, add it
		const FDinoCustomizationAppearanceDomainData NewDomain = FDinoCustomizationAppearanceDomainData(DomainTag, InstanceTag, SubDomains);
		Domains.Add(NewDomain);
		
		return true;
	}


};