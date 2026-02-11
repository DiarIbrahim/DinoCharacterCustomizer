// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerSaveGame.h"
#include "DinoCustomizer/Data/DinoCustomizationAppearence.h"
#include "Kismet/GameplayStatics.h"


FString CHARACTER_APPEARANCE_SAVE_NAME =  "CharacterAppearanceSave";


void UDinoCustomizerSaveGame::AddOrUpdateCustomizationAppearanceToSlot(
	const FDinoCustomizationAppearance& CharacterAppearance, int32 SlotIndex)
{
	if(CharacterAppearanceMap.Contains(SlotIndex) )
	{
		CharacterAppearanceMap[SlotIndex] = CharacterAppearance;
	}else
	{
		CharacterAppearanceMap.Add(SlotIndex, CharacterAppearance);
	}
	
	
}

FDinoCustomizationAppearance UDinoCustomizerSaveGame::LoadCustomizationAppearance(int32 SlotIndex)
{
	if(CharacterAppearanceMap.Contains(SlotIndex) == false) return FDinoCustomizationAppearance();
	return CharacterAppearanceMap[SlotIndex];
}

void UDinoCharacterCustomizerSaveGameHelper::SaveCustomizationAppearance( const FDinoCustomizationAppearance& CharacterAppearance, int32 AppearanceIndex)
{

	UDinoCustomizerSaveGame* AppearanceSaveGame = nullptr;
	
	if(UGameplayStatics::DoesSaveGameExist(CHARACTER_APPEARANCE_SAVE_NAME,0))
	{
		
		AppearanceSaveGame = Cast<UDinoCustomizerSaveGame>(UGameplayStatics::LoadGameFromSlot(CHARACTER_APPEARANCE_SAVE_NAME, 0));
		if(IsValid(AppearanceSaveGame))
		{
			AppearanceSaveGame->AddOrUpdateCustomizationAppearanceToSlot(CharacterAppearance,AppearanceIndex);
		}
		
	}else
	{
		AppearanceSaveGame = Cast<UDinoCustomizerSaveGame>(UGameplayStatics::CreateSaveGameObject(UDinoCustomizerSaveGame::StaticClass()));
		AppearanceSaveGame->AddOrUpdateCustomizationAppearanceToSlot(CharacterAppearance,AppearanceIndex);
	}

	UGameplayStatics::SaveGameToSlot(AppearanceSaveGame,CHARACTER_APPEARANCE_SAVE_NAME,0);
}

FDinoCustomizationAppearance UDinoCharacterCustomizerSaveGameHelper::LoadCustomizationAppearance(const int32 AppearanceIndex)
{
	if(UGameplayStatics::DoesSaveGameExist(CHARACTER_APPEARANCE_SAVE_NAME,0))
	{
		
		UDinoCustomizerSaveGame* AppearanceSaveGame = Cast<UDinoCustomizerSaveGame>(UGameplayStatics::LoadGameFromSlot(CHARACTER_APPEARANCE_SAVE_NAME, 0));
		if(IsValid(AppearanceSaveGame))
		{
			return AppearanceSaveGame->LoadCustomizationAppearance(AppearanceIndex);
		}
	}

	return FDinoCustomizationAppearance();
	
}
