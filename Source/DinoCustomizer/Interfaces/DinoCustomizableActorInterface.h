// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "DinoCustomizableActorInterface.generated.h"




// This class does not need to be modified.
UINTERFACE()
class UDinoCustomizableActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DINOCUSTOMIZER_API IDinoCustomizableActorInterface
{
	GENERATED_BODY()

public:

	// TMap<CustomizableDomain, Customizable Mesh> list of meshes that are customizable
	UFUNCTION(BlueprintNativeEvent)
	TMap<FGameplayTag, UObject*> GetCustomizableDomains() const;

	/*
		the main mesh of the customizable actor, this may be used as location indicator, to get information about sockets
		this can be lead character mesh for characters, or main body mesh for other actor types

		Camera setting uses this to find sockets during camera animation
	 */
	
	UFUNCTION(BlueprintNativeEvent)
	UMeshComponent* GetMainMesh() const;
	
};
