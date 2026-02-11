// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "DinoCustomizerAction.generated.h"


class ADinoCustomizerStudio;

USTRUCT(BlueprintType)
struct FDinoCustomizerActionActivationData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ADinoCustomizerStudio* OwningCustomizerPawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* TargetActor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag TargetDomainTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UObject* TargetDomainObject;

	// this should be false always when called outside character customization pawn, if this true transition montage or other kind of duration-based actions are allowed 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAllowDurationBasedAction = true;

};


/**
 *   Each action represents a separate customization action, like changing a mesh or a color !
 *   sub-class this and make an action type for each action type
 *
 *   Each action will receive :
 *		Target Actor,
 *		Target Domain Tag,
 *		Target Domain Object (Domain Objects are usually a Mesh but can be any object),
 */
UCLASS(Abstract, Blueprintable, EditInlineNew)
class DINOCUSTOMIZER_API UDinoCustomizerAction : public UObject
{
	GENERATED_BODY()


public:


	/*
	 * Identifier of this instance across a domain, this does not need to be unique over all customizable instances, but it must be unique for each domain
	 * e.g. you can have an instance tag called Instance.1 on a domain called 'Lowebody' , instance.1 should never be used more than once on domain 'lowerbody'
	 * but instance.1 can be on multiple domains at the same time.
	 */
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ID")
	FGameplayTag InstanceTag;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	FText ActionDisplayName = FText::FromString("Action");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSoftObjectPtr<UTexture2D> ActionDisplayImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Transition")
	TObjectPtr<UAnimMontage> TransitionAnimMontage;
	

protected:
	
	UPROPERTY(BlueprintReadOnly)
	FDinoCustomizerActionActivationData CurrentActivationData;

public:

	void InitAction(FDinoCustomizerActionActivationData ActivationData);
	UFUNCTION(BlueprintNativeEvent)
	void OnActionStarted(const FDinoCustomizerActionActivationData& ActivationData);
	virtual void OnActionStarted_Implementation(const FDinoCustomizerActionActivationData& ActivationData);



	UFUNCTION(BlueprintNativeEvent)
	bool ValidateAction() const;
	virtual bool ValidateAction_Implementation() const;

	// notifies the changes to the Character Customization pawn if this action called with a valid Character Customization pawn, other wise this call will be ignored
	UFUNCTION(BlueprintCallable)
	void CommitAction();
	
	void EndAction();
	UFUNCTION(BlueprintNativeEvent)
	void OnActionEnded();
	virtual void OnActionEnded_Implementation();

	
};
