// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DinoCustomizer/Components/DinoCustomizerComponent.h"
#include "SubDomain/DinoCustomizerSubAction.h"
#include "SubDomain/DinoCustomizerSubDomain.h"
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
	UDinoCustomizerComponent* OwningComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* TargetActor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag TargetDomainTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UObject* TargetDomainObject;

	// Sub domain instances that are going to apply when this action is applied
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag,FGameplayTag> ActiveSubDomains;

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


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDinoCustomizerActionCommited, UDinoCustomizerAction*, Action);



public:

	/*
	*  Each action can have sub domains (lower level customization to this instance)
	*  Can have multiple customization domains
	*  e.g. materials
	*/
	UPROPERTY(BlueprintReadWrite)
	TArray<UDinoCustomizerSubDomain*> SubDomains;
	
	/*
	 * Identifier of this instance across a domain, this does not need to be unique over all customizable instances, but it must be unique for each domain
	 * e.g. you can have an instance tag called Instance.1 on a domain called 'Lowebody' , instance.1 should never be used more than once on domain 'lowerbody'
	 * but instance.1 can be on multiple domains at the same time.
	 */
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Instance", meta=(Categories="CustomizableInstance"))
	FGameplayTag InstanceTag;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Instance")
	FText ActionDisplayName = FText::FromString("Action Instance");
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Instance")
	TSoftObjectPtr<UTexture2D> ActionDisplayImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Instance")
	TObjectPtr<UAnimMontage> TransitionAnimMontage;



	UPROPERTY(BlueprintAssignable)
	FOnDinoCustomizerActionCommited OnActionCommited;

	

protected:
	
	UPROPERTY(BlueprintReadOnly)
	FDinoCustomizerActionActivationData CurrentActivationData;

	TMap<FGameplayTag, FGameplayTag> CurrentActiveSubDomains;

public:

	void InitAction(FDinoCustomizerActionActivationData ActivationData);
	void ApplyDefaultSubAction();
	UFUNCTION(BlueprintNativeEvent)
	void OnActionStarted(const FDinoCustomizerActionActivationData& ActivationData);
	virtual void OnActionStarted_Implementation(const FDinoCustomizerActionActivationData& ActivationData);



	UFUNCTION(BlueprintNativeEvent)
	bool ValidateAction() const;
	virtual bool ValidateAction_Implementation() const;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnTick(float DeltaTime);
	virtual void OnTick_Implementation(float DeltaTime);
	
	void EndAction(bool bSuccessful = true);
	UFUNCTION(BlueprintNativeEvent)
	void OnActionEnded(bool bSuccessful = true);
	virtual void OnActionEnded_Implementation(bool bSuccessful = true);

	// 
	UFUNCTION(BlueprintNativeEvent)
	bool ShouldReceiveTick();
	virtual bool ShouldReceiveTick_Implementation();

	// when we are confident that the action is done and we are Ok with storing  the change !
	UFUNCTION(BlueprintCallable)
	void CommitAction();

	/*
	 *  To Apply a sub action 
	 */
	UFUNCTION(BlueprintCallable)
	void ApplySubActionOnSubDomain(UDinoCustomizerSubAction* SubAction, const FGameplayTag& SubDomainTag);

	UDinoCustomizerSubDomain* AddSubDomain();
	UDinoCustomizerSubDomain*  DuplicateSubDomain(UDinoCustomizerSubDomain* SubDomainToReplicate);
	bool RemoveSubDomain(UDinoCustomizerSubDomain* SubDomainToRemove);
	bool MoveSubDomainOrderUp(UDinoCustomizerSubDomain* SubDomain);
	bool MoveSubDomainOrderDown(UDinoCustomizerSubDomain* SubDomain);
	
	

	FName GetNewSubDomainName();
	
	
};
