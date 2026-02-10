// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DinoCharacterCustomizer/Actions/DinoCharacterCustomizerAction.h"
#include "DinoCharacterCustomizer/Camera/DinoCharacterCustomizerCameraSettings.h"
#include "Engine/DataAsset.h"
#include "DinoCharacterDataBase.generated.h"




UCLASS()
class DINOCHARACTERCUSTOMIZER_API UDinoCharacterCustomizableDomainData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DomainDisplayName = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UDinoCharacterCustomizerAction*> Instances; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	FDinoCharacterCustomizerCameraSettings CameraSettings;


};


UCLASS()
class DINOCHARACTERCUSTOMIZER_API UDinoCharacterDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, UDinoCharacterCustomizableDomainData*> CustomizableDomains;

	
};

