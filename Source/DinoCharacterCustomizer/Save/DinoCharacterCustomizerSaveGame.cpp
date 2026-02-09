// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCharacterCustomizerSaveGame.h"

#include "Kismet/GameplayStatics.h"


FString CHARACTER_APPEARANCE_SAVE_NAME =  "CharacterAppearanceSave";


void UDinoCharacterCustomizerSaveGame::AddOrUpdateCharacterAppearanceToSlot(
	const FDinoCharacterAppearance& CharacterAppearance, int32 SlotIndex)
{
	if(CharacterAppearanceMap.Contains(SlotIndex) )
	{
		CharacterAppearanceMap[SlotIndex] = CharacterAppearance;
	}else
	{
		CharacterAppearanceMap.Add(SlotIndex, CharacterAppearance);
	}
	
	
}

FDinoCharacterAppearance UDinoCharacterCustomizerSaveGame::LoadCharacterAppearance(int32 SlotIndex)
{
	if(CharacterAppearanceMap.Contains(SlotIndex) == false) return FDinoCharacterAppearance();
	return CharacterAppearanceMap[SlotIndex];
}

void UDinoCharacterCustomizerSaveGameHelper::SaveCharacterAppearance( const FDinoCharacterAppearance& CharacterAppearance, int32 AppearanceIndex)
{

	UDinoCharacterCustomizerSaveGame* AppearanceSaveGame = nullptr;
	
	if(UGameplayStatics::DoesSaveGameExist(CHARACTER_APPEARANCE_SAVE_NAME,0))
	{
		
		AppearanceSaveGame = Cast<UDinoCharacterCustomizerSaveGame>(UGameplayStatics::LoadGameFromSlot(CHARACTER_APPEARANCE_SAVE_NAME, 0));
		if(IsValid(AppearanceSaveGame))
		{
			AppearanceSaveGame->AddOrUpdateCharacterAppearanceToSlot(CharacterAppearance,AppearanceIndex);
		}
		
	}else
	{
		AppearanceSaveGame = Cast<UDinoCharacterCustomizerSaveGame>(UGameplayStatics::CreateSaveGameObject(UDinoCharacterCustomizerSaveGame::StaticClass()));
		AppearanceSaveGame->AddOrUpdateCharacterAppearanceToSlot(CharacterAppearance,AppearanceIndex);
	}

	UGameplayStatics::SaveGameToSlot(AppearanceSaveGame,CHARACTER_APPEARANCE_SAVE_NAME,0);
}

FDinoCharacterAppearance UDinoCharacterCustomizerSaveGameHelper::LoadCharacterAppearance(const int32 AppearanceIndex)
{
	if(UGameplayStatics::DoesSaveGameExist(CHARACTER_APPEARANCE_SAVE_NAME,0))
	{
		
		UDinoCharacterCustomizerSaveGame* AppearanceSaveGame = Cast<UDinoCharacterCustomizerSaveGame>(UGameplayStatics::LoadGameFromSlot(CHARACTER_APPEARANCE_SAVE_NAME, 0));
		if(IsValid(AppearanceSaveGame))
		{
			return AppearanceSaveGame->LoadCharacterAppearance(AppearanceIndex);
		}
	}

	return FDinoCharacterAppearance();
	
}
