// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCharacterCustomizerAction.h"
#include "DinoCharacterCustomizerAction_StaticMesh.generated.h"

/**
 * 
 */
UCLASS()
class DINOCHARACTERCUSTOMIZER_API UDinoCharacterCustomizerAction_StaticMesh : public UDinoCharacterCustomizerAction
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
	UStaticMesh* StaticMesh;


	virtual void OnActionStarted_Implementation(const FDinoCharacterCustomizerActionActivationData& ActivationData) override;

};
