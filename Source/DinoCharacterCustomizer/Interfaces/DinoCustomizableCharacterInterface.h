// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "DinoCustomizableCharacterInterface.generated.h"




// This class does not need to be modified.
UINTERFACE()
class UDinoCustomizableCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DINOCHARACTERCUSTOMIZER_API IDinoCustomizableCharacterInterface
{
	GENERATED_BODY()

public:

	// TMap<CustomizableDomain, Customizable Mesh> list of meshes that are customizable
	UFUNCTION(BlueprintNativeEvent)
	TMap<FGameplayTag, USkeletalMeshComponent*> GetCustomizableDomains() const;
	
};
