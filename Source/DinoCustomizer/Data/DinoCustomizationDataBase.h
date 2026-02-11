// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DinoCustomizer/Camera/DinoCustomizerCameraSettings.h"

#include "Engine/DataAsset.h"
#include "DinoCustomizationDataBase.generated.h"


class UDinoCustomizerAction;

UCLASS()
class DINOCUSTOMIZER_API UDinoCustomizableDomainData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DomainDisplayName = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UDinoCustomizerAction*> Instances; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	FDinoCustomizerCameraSettings CameraSettings;


};


UCLASS()
class DINOCUSTOMIZER_API UDinoCustomizationDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:

	/*
	 *  this is the actor class that we want to customize
	 *  must implement DinoCustomizableActorInterface
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<AActor> CustomizableActorClass;

	
	
	/*
	 *  Domain Data for the actor
	 */ 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, UDinoCustomizableDomainData*> CustomizableDomains;


	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Placement in studio")
	FVector StudioOffsetInStudio = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Placement in studio")
	FRotator RotationOffsetInStudio = FRotator::ZeroRotator;
	
};

