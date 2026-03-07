// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DinoCustomizer/Camera/DinoCustomizerCameraSettings.h"
#include "DinoCustomizer/Data/DinoCustomizationAppearence.h"

#include "GameFramework/Pawn.h"
#include "DinoCustomizerStudio.generated.h"

class UDinoCustomizerDatabase;
class UDinoCustomizationDataBase;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;


/*
 * A possessable pawn which allows you to customize a character that implements DinoCustomizableCharacterInterface
 */

UCLASS()
class DINOCUSTOMIZER_API ADinoCustomizerStudio : public APawn
{
	GENERATED_BODY()


protected:


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Character Customizer|Camera", DisplayName= "Default Camera Setting")
	FDinoCustomizerCameraSettings DefaultCameraSettings;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	// character will sit here
	UPROPERTY(EditAnywhere)
	USceneComponent* CharacterPlacementLocation;
	// Character Direction (Only Y-Axis)
	UPROPERTY(EditAnywhere)
	UArrowComponent* CharacterDirection;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	// current actor we are customizing 
	UPROPERTY(BlueprintReadOnly)
	AActor* CurrentCustomizableActor;
	// current data base we use
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDinoCustomizerDatabase> CurrentCustomizationDataBase;
	// current customizable domains provided buy current customizable actor
	UPROPERTY()
	TMap<FGameplayTag, UObject*> CurrentCustomizableDomains;
	// current main mesh provided by current customizable actor
	UPROPERTY(BlueprintReadOnly)
	UMeshComponent* CurrentCustomizableActorMainMesh;
	// current appearance data for current customizable actor
	UPROPERTY()
	FDinoCustomizationAppearance CurrentCustomizationAppearance;

	// camera settings data currently active 
	UPROPERTY()
	FDinoCustomizerCameraSettings CurrentCameraSettings;
	// target camera settings we are blending to.
	UPROPERTY()
	FDinoCustomizerCameraSettings TargetCameraSettings;

	
public:
	// Sets default values for this actor's properties
	ADinoCustomizerStudio();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;


	UFUNCTION(BlueprintCallable)
	void ApplyCustomizationAppearance(const FDinoCustomizationAppearance& AppearanceData);

	//  starts the customization action, the action still may fail (see action's validation and init) 
	UFUNCTION(BlueprintCallable)
	void ApplyCustomizationActionToDomain(const FGameplayTag& Domain, UDinoCustomizerAction* Action, TMap<FGameplayTag,FGameplayTag> SubDomains);

	//  starts the customization action, the action still may fail (see action's validation and init)
	// not needs sub domains
	UFUNCTION(BlueprintCallable)
	void ApplyCustomizationActionToDomainNoSubDomain(const FGameplayTag& Domain, UDinoCustomizerAction* Action);
	
	
	// this is called by customization actions when they successfully finish, here we update the our character appearance data after actions  
	UFUNCTION(BlueprintCallable)
	void CommitCustomizationActionOnDomain(const FGameplayTag& DomainTag, const FGameplayTag& InstanceTag,  const TMap<FGameplayTag, FGameplayTag>& SubDomains);

	// camera settings
	UFUNCTION(BlueprintCallable)
	void ApplyCameraSettings(const FDinoCustomizerCameraSettings& InCameraSettings);

	// camera settings
	UFUNCTION(BlueprintCallable)
	void ApplyDefaultCameraSettings();

	UFUNCTION(BlueprintCallable)
	bool InitializeCustomizationFromDatabase(UDinoCustomizerDatabase* InDatabase, bool bApplyMinimalAppearanceFromDataBase = true);
	
	UFUNCTION(BlueprintPure)
	FDinoCustomizationAppearance GetCustomizationAppearance() const{ return CurrentCustomizationAppearance;};
	UFUNCTION(BlueprintPure)
	UDinoCustomizerDatabase* GetCustomizationDatabase() const { return CurrentCustomizationDataBase;}
	UFUNCTION(BlueprintPure)
	AActor* GetCurrentCustomizableActor() const { return CurrentCustomizableActor;}
	
protected:

	


	UFUNCTION(BlueprintCallable)
	bool IsCustomizableClassAllowed(TSubclassOf<AActor> InActorClass) const;

	void ApplyCurrentCameraSettings_Internal(const FDinoCustomizerCameraSettings& CameraSettings);
};
