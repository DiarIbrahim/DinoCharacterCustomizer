// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizer/Data/DinoCustomizationAppearence.h"
#include "GameFramework/SaveGame.h"
#include "DinoCustomizerSaveGame.generated.h"




/**
 *   to save a character Appearance and load it later.
 */
UCLASS()
class DINOCUSTOMIZER_API UDinoCustomizerSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<int32, FDinoCustomizationAppearance> CharacterAppearanceMap;

	void AddOrUpdateCustomizationAppearanceToSlot(const FDinoCustomizationAppearance& CharacterAppearance,int32 SlotIndex = 0);
	FDinoCustomizationAppearance LoadCustomizationAppearance(int32 SlotIndex =0);
	
};


UCLASS()
class DINOCUSTOMIZER_API UDinoCharacterCustomizerSaveGameHelper: public UBlueprintFunctionLibrary
{

	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	static void SaveCustomizationAppearance(const FDinoCustomizationAppearance& CustomizationAppearance, int32 AppearanceIndex = 0);
	UFUNCTION(BlueprintCallable)
	static FDinoCustomizationAppearance LoadCustomizationAppearance(const int32 AppearanceIndex = 0);
	
};