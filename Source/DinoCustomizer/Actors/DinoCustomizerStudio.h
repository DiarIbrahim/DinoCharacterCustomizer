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



	/*
	 *   This is a runtime value that allows us to switch on and off the customizable actor rotation around yaw
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dino Customizer|Studio|Camera")
	bool bAllowCustomizableActorYawRotation = true;
	/*
	 *  Should we rotate the actor back to default rotation when we bAllowCustomizableActorRotationAroundYaw to false ?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dino Customizer|Studio|Camera", meta=(EditCondition=bAllowCustomizableActorYawRotation))
	bool bResetRotationToDefaultWhenYawRotationSwitchedOff = true;
	/*
	 *  reset rotation speed
	 */ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dino Customizer|Studio|Camera", meta=(EditCondition=bResetRotationToDefaultWhenYawRotationSwitchedOff))
	float RestRotationToDefaultRotationInterpSpeed = 10.0f;

	// the default camera settings, this set via database
	UPROPERTY()
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

	// camera settings data currently active 
	UPROPERTY()
	FDinoCustomizerCameraSettings CurrentCameraSettings;
	// target camera settings we are blending to.
	UPROPERTY()
	FDinoCustomizerCameraSettings TargetCameraSettings;

	// internal
	bool bResetCustomizableActorRotation = false;


	
public:
	// Sets default values for this actor's properties
	ADinoCustomizerStudio();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;


	// ---- Init
	UFUNCTION(BlueprintCallable)
	bool InitializeStudioFromDatabase(UDinoCustomizerDatabase* InDatabase, bool bApplyMinimalAppearanceFromDataBase = true);


	// ---- Customization
	
	UFUNCTION(BlueprintCallable)
	void ApplyCustomizationAppearance(const FDinoCustomizationAppearance& AppearanceData);

	//  starts the customization action, the action still may fail (see action's validation and init) 
	UFUNCTION(BlueprintCallable)
	void ApplyCustomizationActionToDomain(const FGameplayTag& Domain, UDinoCustomizerAction* Action, TMap<FGameplayTag,FGameplayTag> SubDomains);

	//  starts the customization action, the action still may fail (see action's validation and init)
	// not needs sub domains
	UFUNCTION(BlueprintCallable)
	void ApplyCustomizationActionToDomainNoSubDomain(const FGameplayTag& Domain, UDinoCustomizerAction* Action);

	
	// ---  camera settings

	UFUNCTION(BlueprintCallable)
	void ApplyCameraSettings(const FDinoCustomizerCameraSettings& InCameraSettings);
	UFUNCTION(BlueprintCallable)
	void ApplyDefaultCameraSettings();
	// to rotate actor around Yaw, bAllowCustomizableActorYawRotation need to be true to allow this
	UFUNCTION(BlueprintCallable)
	void AddCustomizableActorYawRotation(float Yaw);
	// resets the customizable actor rotation around Yaw axis to default rotation 
	UFUNCTION(BlueprintCallable)
	void ResetCustomizableActorYawRotation();
	UFUNCTION(BlueprintCallable)
	void SetAllowCustomizableActorYawRotation(bool bValue);


	// --- Getters
	
	UFUNCTION(BlueprintPure)
	FDinoCustomizationAppearance GetCustomizationAppearance();
	UFUNCTION(BlueprintPure)
	UDinoCustomizerDatabase* GetCustomizationDatabase() const { return CurrentCustomizationDataBase;}
	UFUNCTION(BlueprintPure)
	AActor* GetCurrentCustomizableActor() const { return CurrentCustomizableActor;}
	
protected:

	


	UFUNCTION(BlueprintCallable)
	bool IsCustomizableClassAllowed(TSubclassOf<AActor> InActorClass) const;

	void ApplyCurrentCameraSettings_Internal(const FDinoCustomizerCameraSettings& CameraSettings);

	
};
