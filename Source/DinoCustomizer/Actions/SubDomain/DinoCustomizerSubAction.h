// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "DinoCustomizerSubAction.generated.h"



/*
 *  Each action can have a sub actions
 *  they can do simple changes each instance of the action
 *
 *  mostly running on an instance of a customization domain
 *
 *  e.g.
 *
 *  you have a domain called Upper body
 *  You want to Apply a jacket as a customization to the upper body domain
 *   you can also apply a change to the jacket like a material update using Sub actions
 */

class UDinoCustomizerAction;

UCLASS(Abstract, Blueprintable, EditInlineNew)
class DINOCUSTOMIZER_API UDinoCustomizerSubAction : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sub Instance", meta = (Categories = "CustomizableSubInstance"))
	FGameplayTag SubInstanceTag = {};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sub Instance")
	FText SubInstanceDisplayName = FText::FromString("Sub Instance");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sub Instance")
	TSoftObjectPtr<UTexture2D> SubInstanceDisplayImage;

	void InitAction(UDinoCustomizerAction* OwnerAction, UObject* TargetObject);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnActionStarted(UDinoCustomizerAction* OwnerAction, UObject* TargetObject);
	virtual void OnActionStarted_Implementation(UDinoCustomizerAction* OwnerAction, UObject* TargetObject);
	
};

USTRUCT(BlueprintType)
struct FDinoCustomizerSubDomainContainer
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText SubActionDisplayName = {};

	// will automatically apply sub action 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bApplyFirstSubAction = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	TArray<UDinoCustomizerSubAction*> SubActions;

	UDinoCustomizerSubAction* FindSubDomainInstance(const FGameplayTag& InstanceTag)
	{
		for (UDinoCustomizerSubAction* SubAction : SubActions)
		{
			if(IsValid(SubAction) && SubAction->SubInstanceTag.MatchesTagExact(InstanceTag))
			{
				return SubAction;
			}
		}
		return nullptr;
	}
	
};

