// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizerSubAction.h"
#include "DinoCustomizerSubAction_ApplyMaterial.generated.h"

/**
 * 
 */
UCLASS()
class DINOCUSTOMIZER_API UDinoCustomizerSubAction_ApplyMaterial : public UDinoCustomizerSubAction
{
	GENERATED_BODY()

	public:

	UDinoCustomizerSubAction_ApplyMaterial();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Material")
	TSoftObjectPtr<UMaterialInterface> Material;

	virtual void OnActionStarted_Implementation(UDinoCustomizerAction* OwnerAction, UObject* TargetObject) override;
};
