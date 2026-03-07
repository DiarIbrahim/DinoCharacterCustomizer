// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerDatabaseAssetAction.h"
#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"
#include "DinoCustomizerEditor/EditorApp/DinoCustomizerDatabaseEditorApp.h"
#include "DinoCustomizerEditor/Other/Colors.h"

FDinoCustomizerDatabaseAssetAction::FDinoCustomizerDatabaseAssetAction(EAssetTypeCategories::Type InAssetCategory)
{
	AssetCategory = InAssetCategory;
}

FText FDinoCustomizerDatabaseAssetAction::GetName() const
{
	return FText::FromString("Dino Customizer Database");
}

FColor FDinoCustomizerDatabaseAssetAction::GetTypeColor() const
{
	return DinoColors::GetMainColor();
}

uint32 FDinoCustomizerDatabaseAssetAction::GetCategories()
{
	return AssetCategory;
}

UClass* FDinoCustomizerDatabaseAssetAction::GetSupportedClass() const
{
	return UDinoCustomizerDatabase::StaticClass();
}

void FDinoCustomizerDatabaseAssetAction::OpenAssetEditor(const TArray<UObject*>& InObjects,
	const EAssetTypeActivationOpenedMethod OpenedMethod, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ?  EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for(UObject* Obj : InObjects)
	{
		if(UDinoCustomizerDatabase* DB = Cast<UDinoCustomizerDatabase>(Obj))
		{
			TSharedRef<FDinoCustomizerDatabaseEditorApp> Editor(new FDinoCustomizerDatabaseEditorApp);
			Editor->OpenEditor(Mode,EditWithinLevelEditor, DB);
		}
	}
	
}
