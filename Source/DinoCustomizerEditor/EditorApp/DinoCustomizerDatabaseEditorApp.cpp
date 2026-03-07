// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerDatabaseEditorApp.h"

#include "DinoCustomizerDatabaseAppMode.h"
#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"

void FDinoCustomizerDatabaseEditorApp::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);

}

void FDinoCustomizerDatabaseEditorApp::OpenEditor(const EToolkitMode::Type Mode,
	const TSharedPtr<class IToolkitHost>& InToolkitHost, UObject* InObject)
{

	DataBase = Cast<UDinoCustomizerDatabase>(InObject);

	if(DataBase.IsValid() == false) return;
	
	InitAssetEditor(
		Mode,
		InToolkitHost,
		FName("Dino Customizer Database Editor"),
		FTabManager::FLayout::NullLayout,
		true,
		true,
		{InObject}
		);

	AddApplicationMode(TEXT("DinoCustomizerDatabaseAppMode"), MakeShareable(new FDinoCustomizerDatabaseAppMode(SharedThis(this))));

	SetCurrentMode(TEXT("DinoCustomizerDatabaseAppMode"));
	
}
