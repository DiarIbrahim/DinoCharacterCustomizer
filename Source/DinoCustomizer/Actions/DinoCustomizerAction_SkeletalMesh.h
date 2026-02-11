// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizerAction.h"
#include "DinoCustomizerAction_SkeletalMesh.generated.h"

/**
 * 
 */
UCLASS()
class DINOCUSTOMIZER_API UDinoCustomizerAction_SkeletalMesh : public UDinoCustomizerAction
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;


	virtual void OnActionStarted_Implementation(const FDinoCustomizerActionActivationData& ActivationData) override;

};
