// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Net/Serialization/FastArraySerializer.h"

#include "DinoCharacterAppearence.generated.h"


/*
 *  a Domain is any customizable part of the character like Hand, upperBody, lowerBody and so on
 *  an Instance is an instance or a change that can be applied to the domain, e.g. like a hair style that can be applied to hair domain
 */

USTRUCT(BlueprintType)
struct  FDinoCharacterAppearanceDomainData : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FDinoCharacterAppearanceDomainData(){}
	FDinoCharacterAppearanceDomainData(FGameplayTag InDomainTag, FGameplayTag InInstanceTag):DomainTag(InDomainTag), InstanceTag(InInstanceTag){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag DomainTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag InstanceTag;
	
	
};


/*
 *		a light weight data that is representing the character's Appearance
 *		good to be used to store or transfer over network
 */
USTRUCT(BlueprintType)
struct FDinoCharacterAppearance : public FFastArraySerializer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDinoCharacterAppearanceDomainData> Domains;
	
	bool AddOrUpdateDomainData(FGameplayTag DomainTag, FGameplayTag InstanceTag)
	{
		if(DomainTag.IsValid() == false) return false;
		
		for(FDinoCharacterAppearanceDomainData& Data : Domains)
		{
			if(Data.DomainTag.MatchesTagExact(DomainTag))
			{
				Data.InstanceTag = InstanceTag;
				return true;
			}
		}

		// the domain is not there, add it
		const FDinoCharacterAppearanceDomainData NeWDomain = FDinoCharacterAppearanceDomainData(DomainTag, InstanceTag);
		Domains.Add(NeWDomain);
		
		return true;
	}

	TMap<FGameplayTag, FGameplayTag> GetDomainsAsMap() const
	{
		TMap<FGameplayTag, FGameplayTag> Map;
		for(const FDinoCharacterAppearanceDomainData& Data : Domains)
		{
			Map.Add(Data.DomainTag, Data.InstanceTag);
		}
		return Map;
	}

};