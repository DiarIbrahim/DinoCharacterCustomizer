// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCharacterCustomizer/Data/DinoCharacterAppearence.h"
#include "DinoCharacterCustomizer/Data/DinoCharacterDataBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DinoCharacterCustomizerHelper.generated.h"

class ADinoCharacterCustomizerPawn;
/**
 * 
 */
UCLASS()
class UDinoCharacterCustomizerHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:


	/*
	 *  Returns the Instance data for the provided tag for the specified Domain inside the database
	 *  e.g. to get jacket (the instance tag) for the upperbody (the domain tag) in side the database 
	 */
	UFUNCTION(BlueprintCallable, Category = "Dino Character Customizer")
	static UDinoCharacterCustomizerAction* GetCharacterInstanceDataFromDatabase(UDinoCharacterDataBase* InDatabase, FGameplayTag Domain, FGameplayTag InstanceTag);

	/*
	 *   -- loads a character appearance data as a map of Domains and instance data (not used but may be helpful )
	 */
	UFUNCTION(BlueprintCallable, Category = "Dino Character Customizer")
	static  TMap<FGameplayTag, UDinoCharacterCustomizerAction*> LoadCharacterAppearanceData(UDinoCharacterDataBase* InDatabase,const FDinoCharacterAppearance& CharacterAppearance);

	/*
	 *  generate a minimal character appearance from the provided data base
	 *  NOTE : this will provide an instance (first index) for any domain inside the database, regardless of your character's custom domains
	 *  Use GenerateMinimalCharacterAppearanceFromDataBaseByCharacter if you want to only get domains provided by the character (the character must implement IDinoCustomizableCharacterInterface)
	 */
	UFUNCTION(BlueprintCallable, Category = "Dino Character Customizer")
	static FDinoCharacterAppearance GenerateMinimalCharacterAppearanceFromDatabase(UDinoCharacterDataBase* InDatabase);

	/*
	 *  generate a minimal character appearance from the provided data base
	 *  returns an instance (first index) for each domain provided by the character (the character must implement IDinoCustomizableCharacterInterface)
	 */
	UFUNCTION(BlueprintCallable, Category = "Dino Character Customizer")
	static FDinoCharacterAppearance GenerateMinimalCharacterAppearanceFromDatabaseForCharacter(UDinoCharacterDataBase* InDatabase,  ACharacter* Character);

	/*
	 *  Generates a random character appearance data from the database
	 *  will generate an instance data for each domain in the database regardless of the character
	 */
	UFUNCTION(BlueprintCallable, Category = "Dino Character Customizer")
	static FDinoCharacterAppearance GenerateRandomCharacterAppearanceFromDatabase(UDinoCharacterDataBase* InDatabase);

	/*
	*  Generates a random character appearance data from the database
	*  will generate an instance data for each domain in the database for each domain provided by character (the character must implement IDinoCustomizableCharacterInterface)
	*/
	UFUNCTION(BlueprintCallable, Category = "Dino Character Customizer")
	static FDinoCharacterAppearance GenerateRandomCharacterAppearanceFromDatabaseForCharacter(UDinoCharacterDataBase* InDatabase, ACharacter* Character);


	/*
	 *  returns an instance tag on a specific domain inside a character appearance
	 */
	UFUNCTION(BlueprintCallable, Category = "Dino Character Customizer")
	static FGameplayTag GetCharacterAppearanceDomainInstance(const FDinoCharacterAppearance& CharacterAppearance, FGameplayTag DomainTag);
	
};
