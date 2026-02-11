// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"

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
	UFUNCTION(BlueprintCallable, Category = "Dino Character Customizer")
	static UDinoCustomizerAction* GetCustomizationInstanceDataFromDatabase(UDinoCustomizationDataBase* InDatabase, FGameplayTag Domain, FGameplayTag InstanceTag);

	/*
	 *   -- loads a character appearance data as a map of Domains and instance data (not used but may be helpful )
	 */
	UFUNCTION(BlueprintCallable, Category = "Dino Character Customizer")
	static  TMap<FGameplayTag, UDinoCustomizerAction*> LoadCharacterAppearanceData(UDinoCustomizationDataBase* InDatabase,const FDinoCustomizationAppearance& CharacterAppearance);

	/*
	 *  generate a minimal character appearance from the provided data base
	 *  NOTE : this will provide an instance (first index) for any domain inside the database, regardless of your character's custom domains
	 *  Use GenerateMinimalCharacterAppearanceFromDataBaseByCharacter if you want to only get domains provided by the character (the character must implement IDinoCustomizableCharacterInterface)
	 */
	UFUNCTION(BlueprintCallable, Category = "Dino Character Customizer")
	static FDinoCustomizationAppearance GenerateMinimalCustomizationAppearanceFromDatabase(UDinoCustomizationDataBase* InDatabase);
	
	/*
	 *  Generates a random character appearance data from the database
	 *  will generate an instance data for each domain in the database regardless of the character
	 */
	UFUNCTION(BlueprintCallable, Category = "Dino Character Customizer")
	static FDinoCustomizationAppearance GenerateRandomCustomizationAppearanceFromDatabase(UDinoCustomizationDataBase* InDatabase);



	/*
	 *  returns an instance tag on a specific domain inside a character appearance
	 */
	UFUNCTION(BlueprintCallable, Category = "Dino Character Customizer")
	static FGameplayTag GetCharacterAppearanceDomainInstance(const FDinoCustomizationAppearance& CharacterAppearance, FGameplayTag DomainTag);
	
};
