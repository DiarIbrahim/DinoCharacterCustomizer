// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizerAction.h"
#include "DinoCustomizerAction_StaticMesh.generated.h"

/**
 * 
 */
UCLASS()
class DINOCUSTOMIZER_API UDinoCustomizerAction_StaticMesh : public UDinoCustomizerAction
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
	UStaticMesh* StaticMesh;


	virtual void OnActionStarted_Implementation(const FDinoCustomizerActionActivationData& ActivationData) override;

};
