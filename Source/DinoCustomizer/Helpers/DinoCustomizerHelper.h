// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "DinoCustomizerHelper.generated.h"

class ADinoCustomizerStudio;
/**
 * 
 */
UCLASS()
class DINOCUSTOMIZER_API UDinoCustomizerHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:


	/*
	 *  Returns the Instance data for the provided tag for the specified Domain inside the database
	 *  e.g. to get jacket (the instance tag) for the upperbody (the domain tag) in side the database 
	 */
	UFUNCTION(BlueprintCallable, Category = "Dino Customizer")
	static UDinoCustomizerAction* GetCustomizationInstanceDataFromDatabase(UDinoCustomizerDatabase* InDatabase, FGameplayTag Domain, FGameplayTag InstanceTag);


	/*
	 *  generate a minimal character appearance from the provided data base
	 *  NOTE : this will provide an instance (first index) for any domain inside the database, regardless of your character's custom domains
	 *  Use GenerateMinimalCharacterAppearanceFromDataBaseByCharacter if you want to only get domains provided by the character (the character must implement IDinoCustomizableCharacterInterface)
	 */
	UFUNCTION(BlueprintCallable, Category = "Dino Customizer")
	static FDinoCustomizationAppearance GenerateMinimalCustomizationAppearanceFromDatabase(UDinoCustomizerDatabase* InDatabase);
	
	/*
	 *  Generates a random character appearance data from the database
	 *  will generate an instance data for each domain in the database regardless of the character
	 */
	UFUNCTION(BlueprintCallable, Category = "Dino Customizer")
	static FDinoCustomizationAppearance GenerateRandomCustomizationAppearanceFromDatabase(UDinoCustomizerDatabase* InDatabase, bool bSelectRandomForEachSubDomainForAllDomains = true);
	
	/*
	 *  returns an instance tag on a specific domain inside a character appearance
	 */
	UFUNCTION(BlueprintPure, Category = "Dino Customizer")
	static FGameplayTag GetAppearanceDomainInstance(const FDinoCustomizationAppearance& CharacterAppearance, FGameplayTag DomainTag);

	/*
 *  returns an instance tag on a specific domain inside a character appearance
 */
	UFUNCTION(BlueprintPure, Category = "Dino Customizer")
	static FGameplayTag GetAppearanceSubDomainInstance(const FDinoCustomizationAppearance& CharacterAppearance, FGameplayTag DomainTag, FGameplayTag SubDomainTag);


	// by providing a list of instance tags, it will return next tag child of "CustomizableInstance" tag if any left 
	UFUNCTION(BlueprintPure, Category = "Dino Customizer")
	static FGameplayTag GetNextUnUsedCustomizableInstanceTag(const FGameplayTagContainer& UsedTags);

	// by providing a list of instance tags, it will return next tag child of "CustomizableSubInstance" tag if any left 
	UFUNCTION(BlueprintPure, Category = "Dino Customizer")
	static FGameplayTag GetNextUnUsedCustomizableSubInstanceTag(const FGameplayTagContainer& UsedTags);




	// debug
	UFUNCTION(BlueprintCallable, Category = "Dino Customizer", meta = (WorldContext = "WorldContextObject"))
	static void DebugPrintAppearance(const FDinoCustomizationAppearance& Appearance, float Duration  = 1.0f,FLinearColor Color = FLinearColor::Blue);
	
	
};
