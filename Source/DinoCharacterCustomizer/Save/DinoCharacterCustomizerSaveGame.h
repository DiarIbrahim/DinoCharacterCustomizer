// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCharacterCustomizer/Data/DinoCharacterAppearence.h"
#include "GameFramework/SaveGame.h"
#include "DinoCharacterCustomizerSaveGame.generated.h"




/**
 *   to save a character Appearance and load it later.
 */
UCLASS()
class DINOCHARACTERCUSTOMIZER_API UDinoCharacterCustomizerSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<int32, FDinoCharacterAppearance> CharacterAppearanceMap;

	void AddOrUpdateCharacterAppearanceToSlot(const FDinoCharacterAppearance& CharacterAppearance,int32 SlotIndex = 0);
	FDinoCharacterAppearance LoadCharacterAppearance(int32 SlotIndex =0);
	
};


UCLASS()
class DINOCHARACTERCUSTOMIZER_API UDinoCharacterCustomizerSaveGameHelper: public UBlueprintFunctionLibrary
{

	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	static void SaveCharacterAppearance(const FDinoCharacterAppearance& CharacterAppearance, int32 AppearanceIndex = 0);
	UFUNCTION(BlueprintCallable)
	static FDinoCharacterAppearance LoadCharacterAppearance(const int32 AppearanceIndex = 0);
	
};