// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizerSubAction.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "DinoCustomizerSubDomain.generated.h"


UCLASS(BlueprintType)
class DINOCUSTOMIZER_API UDinoCustomizerSubDomain : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubDomain", meta = (Categories = "CustomizableSubDomain"))
	FGameplayTag SubDomainTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubDomain")
	FText SubDomainDisplayName = FText::FromString("Sub Domain");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubDomain")
	TSoftObjectPtr<UTexture2D> SubDomainDisplayImage;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<UDinoCustomizerSubAction*> SubInstances;

	UDinoCustomizerSubAction* AddSubInstances(TSubclassOf<UDinoCustomizerSubAction> SubInstanceClass);
	UDinoCustomizerSubAction* DuplicateSubInstances(UDinoCustomizerSubAction* SourceSubInstance);
	bool RemoveSubInstances(UDinoCustomizerSubAction* SubInstanceToRemove);
	void GetNewInstanceName(FName& NewActionName);
};
