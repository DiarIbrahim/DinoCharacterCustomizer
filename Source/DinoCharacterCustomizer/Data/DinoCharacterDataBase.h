// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DinoCharacterDataBase.generated.h"


USTRUCT(BlueprintType)
struct DINOCHARACTERCUSTOMIZER_API FDinoCustomizableInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag CustomizableInstanceTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USkeletalMesh> InstanceMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category= "UI Data")
	FText DisplayName {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category= "UI Data")
	TSoftObjectPtr<UTexture2D> DisplayImage  = nullptr;
	
	// override the animation montage for this instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transition")
	UAnimMontage* TransactionMontageOverride = nullptr;
};



UCLASS()
class DINOCHARACTERCUSTOMIZER_API UDinoCharacterCustomizableDomainData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	// customizable instances of this domain 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDinoCustomizableInstanceData> Instances;

	// name of this customizable section name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UI Data")
	FText DomainDisplayName = {};

	// optional display icon for the domain
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "UI Data")
	TSoftObjectPtr<UTexture2D> DomainIcon  = nullptr;
	
	// montage to play on the character when this domain mesh changed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Transition")
	UAnimMontage* TransactionMontage = nullptr;

};


UCLASS()
class DINOCHARACTERCUSTOMIZER_API UDinoCharacterDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, UDinoCharacterCustomizableDomainData*> CustomizableDomains;
	
};

