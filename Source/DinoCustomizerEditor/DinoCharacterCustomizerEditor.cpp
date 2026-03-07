// Copyright Epic Games, Inc. All Rights Reserved.

#include "DinoCharacterCustomizerEditor.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "AssetAction/DinoCustomizerDatabaseAssetAction.h"

#define LOCTEXT_NAMESPACE "FDinoCharacterCustomizerModule"

void FDinoCustomizerEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools& AssetTools = IAssetTools::Get();
	EAssetTypeCategories::Type Category = AssetTools.RegisterAdvancedAssetCategory(FName("Dino"), FText::FromString("Dino"));
	TSharedPtr<FDinoCustomizerDatabaseAssetAction> Action = MakeShareable<FDinoCustomizerDatabaseAssetAction>(new FDinoCustomizerDatabaseAssetAction(Category));
	AssetTools.RegisterAssetTypeActions(Action.ToSharedRef());
}

void FDinoCustomizerEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDinoCustomizerEditorModule, FDinoCustomizerEditorModule)