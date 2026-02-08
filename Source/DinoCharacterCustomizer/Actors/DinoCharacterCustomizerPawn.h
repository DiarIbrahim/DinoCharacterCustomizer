// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/TextRenderComponent.h"
#include "DinoCharacterCustomizer/Data/DinoCharacterAppearence.h"
#include "DinoCharacterCustomizer/Data/DinoCharacterDataBase.h"
#include "GameFramework/Pawn.h"
#include "DinoCharacterCustomizerPawn.generated.h"

class UCameraComponent;
class UArrowComponent;


/*
 * A possesable pawn which allows you to customize a character that implements DinoCustomizableCharacterInterface
 */

UCLASS()
class DINOCHARACTERCUSTOMIZER_API ADinoCharacterCustomizerPawn : public APawn
{
	GENERATED_BODY()


protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Customizer")
	TObjectPtr<UDinoCharacterDataBase> CharacterDataBase;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Customizer")
	TSubclassOf<ACharacter> CharacterClass;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Customizer|Camera")
	float DefaultCameraDistance = 300.0f;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	// character will sit here
	UPROPERTY(EditAnywhere)
	USceneComponent* CharacterPlacementLocation;
	// Character Direction (Only Y-Axis)
	UPROPERTY(EditAnywhere)
	UArrowComponent* CharacterDirection;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;


	UPROPERTY()
	ACharacter* Character;

	UPROPERTY()
	TMap<FGameplayTag, USkeletalMeshComponent*> CharacterCustomizableDomains;
	UPROPERTY()
	FDinoCharacterAppearance CurrentCharacterAppearance;

	
public:
	// Sets default values for this actor's properties
	ADinoCharacterCustomizerPawn();

protected:

	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	void InitializeCharacter();

	UFUNCTION(BlueprintCallable)
	bool IsCharacterClassAllowed(TSubclassOf<ACharacter> InCharacterClass) const;
	
	UFUNCTION(BlueprintCallable)
	void ApplyCharacterAppearance(const FDinoCharacterAppearance& CharacterAppearance);
	
	UFUNCTION(BlueprintCallable)
	FDinoCharacterAppearance GetCharacterAppearance() const{ return CurrentCharacterAppearance;};

	UFUNCTION(BlueprintCallable)
	void ModifyCustomizableDomainMesh(FGameplayTag Domain, FGameplayTag InstanceTag);
};
