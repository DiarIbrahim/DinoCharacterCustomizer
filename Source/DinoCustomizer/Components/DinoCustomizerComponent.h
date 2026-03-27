// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "DinoCustomizer/Data/DinoCustomizationAppearence.h"
#include "DinoCustomizerComponent.generated.h"

class ADinoCustomizerStudio;
class UDinoCustomizerAction;


/*
 *  This component lives inside any character that wants to be customizable
 *  handles Customizations, and works as interface between CustomizerStudio and Customizable Character
 * 
 */

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DINOCUSTOMIZER_API UDinoCustomizerComponent : public UActorComponent
{
	GENERATED_BODY()



protected:

	// list of customizable domains of the owner 
	TMap<FGameplayTag /*Domain Tag*/, TArray<UObject*>> DomainData;

	// only one instance can be active on each domain
	UPROPERTY()
	TMap<FGameplayTag /*Domain Tag*/, UDinoCustomizerAction*> ActiveDomainInstances;

	// current appearance data for current customizable actor
	UPROPERTY()
	FDinoCustomizationAppearance CustomizationAppearance;
	
protected:
	
	UDinoCustomizerComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,    FActorComponentTickFunction* ThisTickFunction) override;

public:

	/*
	 *  Registers a customizable domain with list of objects that belong to the domain (or can be affected by domain)
	 */ 
	UFUNCTION(BlueprintCallable, Category="DinoCustomizer", meta=(Categories="CustomizableDomain"))
	void RegisterDomain(FGameplayTag DomainTag,TArray<UObject*> DomainObjects);

	UFUNCTION(BlueprintCallable, Category="DinoCustomizer")
	FDinoCustomizationAppearance GetAppearance(){return CustomizationAppearance;}

	UFUNCTION(BlueprintCallable, Category="DinoCustomizer", meta=(Categories="CustomizableDomain"))
	bool ApplyInstanceToDomain(FGameplayTag InDomainTag, UDinoCustomizerAction* Instance);
	bool ApplyInstanceToDomainFromStudio(ADinoCustomizerStudio* Studio, FGameplayTag InDomainTag, UDinoCustomizerAction* Instance, TMap<FGameplayTag,FGameplayTag> SubDomains);
	UFUNCTION(BlueprintCallable, Category="DinoCustomizer", meta=(Categories="CustomizableDomain"))
	bool ApplyInstanceToDomainWithSubDomainData(FGameplayTag InDomainTag, UDinoCustomizerAction* Instance, TMap<FGameplayTag,FGameplayTag> SubDomains);

	void CommitAction(UDinoCustomizerAction* Action,const FGameplayTag& DomainTag, TMap<FGameplayTag,FGameplayTag> SubDomains);

private:

	
	bool ApplyInstanceToDomain_Internal(ADinoCustomizerStudio* Studio, FGameplayTag InDomainTag, UDinoCustomizerAction* Instance, TMap<FGameplayTag,FGameplayTag> SubDomains);
	
};
