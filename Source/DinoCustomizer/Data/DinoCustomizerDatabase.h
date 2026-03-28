// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DinoCustomizer/Camera/DinoCustomizerCameraSettings.h"
#include "UObject/Object.h"
#include "DinoCustomizerDatabase.generated.h"




class UDinoCustomizerAction;

UCLASS(EditInlineNew, BlueprintType)
class DINOCUSTOMIZER_API UDinoCustomizerDatabaseDomain : public UObject
{
	GENERATED_BODY()

public:

	UDinoCustomizerDatabaseDomain();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Domain Settings")
	FText DomainDisplayName = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category= "Domain Settings", meta=(Categories = "CustomizableDomain"))
	FGameplayTag DomainTag;


	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category= "Domain Settings|Visual")
	FLinearColor DomainColor = FLinearColor::White;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Domain Settings|Camera")
	FDinoCustomizerCameraSettings CameraSettings;
	
	UPROPERTY(BlueprintReadOnly, Instanced)
	TArray<UDinoCustomizerAction*> Instances; 

	
	bool operator==(const UDinoCustomizerDatabaseDomain& other) const
	{
		return DomainId == other.DomainId;
	}

	FGuid GetDomainId() const { return DomainId; }
	FText GetDomainDisplayName() const { return DomainDisplayName.IsEmpty() ? FText::FromString(GetName()) : DomainDisplayName; }


	UDinoCustomizerAction* AddNewInstance(TSubclassOf<UDinoCustomizerAction> ActionClass);
	UDinoCustomizerAction* DuplicateInstance(UDinoCustomizerAction* Instance);
	bool RemoveInstance(UDinoCustomizerAction* Instance);

	bool MoveInstanceOrderDown(UDinoCustomizerAction* Instance);
	bool MoveInstanceOrderUp(UDinoCustomizerAction* Instance);

	void GetNewInstanceName(FName& NewActionName);
	// tries to fill instance tag for new Instance if valid instances tags left
	FGameplayTag GetNewInstanceTag();
	
	/*
	 *   Returns instance of the domain by tag
	 */
	UFUNCTION(BlueprintCallable, meta=(Categories = "CustomizableInstance"))
	UDinoCustomizerAction* GetInstanceByTag(FGameplayTag InInstanceTag);

	/*
	 * Returns random instance
	 * 
	 */
	UFUNCTION(BlueprintCallable)
	UDinoCustomizerAction* GetRandomInstance();

	/*
	 *   Returns First Instance
	 */
	UFUNCTION(BlueprintCallable)
	UDinoCustomizerAction* GetMinimalInstance();

private:

	FGuid DomainId;

};



UCLASS(BlueprintType)
class DINOCUSTOMIZER_API UDinoCustomizerDatabase : public UObject
{
	GENERATED_BODY()

public:



	// ---- Settings
	
	/*
	*  this is the actor class that we want to customize
	*  must implement DinoCustomizableActorInterface
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UClass* CustomizableActorClass;
	/*
	*  The actors placement Location offset in the studio
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector ActorPlacementLocationOffset;
	/*
	 *  actor placement rotation offset in the studio
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator ActorPlacementRotationOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Camera")
	FDinoCustomizerCameraSettings DefaultCameraSettings;

	// ----


	

	UPROPERTY(BlueprintReadOnly, Instanced)
	TArray<UDinoCustomizerDatabaseDomain*> Domains;


	UDinoCustomizerDatabaseDomain* AddNewDatabaseDomain();
	bool RemoveDatabaseDomain(UDinoCustomizerDatabaseDomain* Domain);
	UDinoCustomizerDatabaseDomain* DuplicateDatabaseDomain(UDinoCustomizerDatabaseDomain* Domain);

	bool MoveDomainOrderUp(UDinoCustomizerDatabaseDomain* Domain);
	bool MoveDomainOrderDown(UDinoCustomizerDatabaseDomain* Domain);


	UFUNCTION(BlueprintCallable, meta=(Categories = "CustomizableDomain"))
	UDinoCustomizerDatabaseDomain* GetDomainByTag(FGameplayTag InDomainTag);

	FName GetNewDatabaseDomainName();
};



