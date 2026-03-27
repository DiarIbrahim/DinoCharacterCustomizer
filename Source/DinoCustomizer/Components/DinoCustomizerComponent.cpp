// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerComponent.h"

#include "DinoCustomizer/Actions/DinoCustomizerAction.h"


// Sets default values for this component's properties
UDinoCustomizerComponent::UDinoCustomizerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDinoCustomizerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDinoCustomizerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for(const auto& Pair : ActiveDomainInstances)
	{
		UDinoCustomizerAction* ActiveInstance = Pair.Value;
		
		if(IsValid(ActiveInstance))
		{
			if(ActiveInstance->ShouldReceiveTick()){
				ActiveInstance->OnTick(DeltaTime);
			}
		}
	}
	
}

void UDinoCustomizerComponent::RegisterDomain(FGameplayTag DomainTag, TArray<UObject*> DomainObjects)
{
	// empty
	if(DomainObjects.IsEmpty()) return;

	// at least one valid obj
	if(IsValid(DomainObjects[0]) == false) return;
	
	DomainData.Add(DomainTag, DomainObjects);

}

bool UDinoCustomizerComponent::ApplyInstanceToDomain(FGameplayTag InDomainTag, UDinoCustomizerAction* Instance)
{
	return ApplyInstanceToDomain_Internal(nullptr, InDomainTag, Instance, {});
}

bool UDinoCustomizerComponent::ApplyInstanceToDomainWithSubDomainData(FGameplayTag InDomainTag, UDinoCustomizerAction* Instance, TMap<FGameplayTag, FGameplayTag> SubDomains)
{
	return ApplyInstanceToDomain_Internal(nullptr, InDomainTag, Instance, SubDomains);
}

void UDinoCustomizerComponent::CommitAction(UDinoCustomizerAction* Action, const FGameplayTag& DomainTag,
	TMap<FGameplayTag, FGameplayTag> SubDomains)
{
	
	// get (or add and get) appearance domain data
	FDinoCustomizationAppearanceDomainData& TargetDomainData = CustomizationAppearance.GetDomainData(DomainTag);
	TargetDomainData.InstanceTag = Action->InstanceTag;
	TargetDomainData.SetSubDomainsFromMap(SubDomains);
	
}



bool UDinoCustomizerComponent::ApplyInstanceToDomainFromStudio(ADinoCustomizerStudio* Studio, FGameplayTag InDomainTag, UDinoCustomizerAction* Instance, TMap<FGameplayTag, FGameplayTag> SubDomains)
{
	return ApplyInstanceToDomain_Internal(Studio, InDomainTag, Instance, SubDomains);
}

bool UDinoCustomizerComponent::ApplyInstanceToDomain_Internal(ADinoCustomizerStudio* Studio, FGameplayTag InDomainTag,  UDinoCustomizerAction* Instance, TMap<FGameplayTag,FGameplayTag> SubDomains)
{
	if(ActiveDomainInstances.Contains(InDomainTag))
	{
		// there is an active instance running on this domain, first lets end and remove it
		UDinoCustomizerAction* Action = *ActiveDomainInstances.Find(InDomainTag);
		Action->EndAction();

		ActiveDomainInstances.Remove(InDomainTag);
	}

	// check if domain registered
	if(DomainData.Contains(InDomainTag) == false)
	{
		// not registered
		return false;
	}
	
	
	FDinoCustomizerActionActivationData ActionData = FDinoCustomizerActionActivationData();
	ActionData.OwningCustomizerPawn = Studio;
	ActionData.OwningComponent = this;
	ActionData.TargetActor = GetOwner();
	ActionData.TargetDomainTag = InDomainTag;
	ActionData.TargetDomainObject = DomainData[InDomainTag][0];
	ActionData.ActiveSubDomains = SubDomains;

	Instance->InitAction(ActionData);
	
	ActiveDomainInstances.Add(InDomainTag, Instance);
	
	return true;
}

