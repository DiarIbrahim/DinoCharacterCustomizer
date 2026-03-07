// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerDatabaseAppMode.h"

#include "DinoCustomizerDatabaseEditorApp.h"
#include "DinoCustomizerDatabasePrimaryTabFactory.h" 
#include "DinoCustomizerDatabaseStudioTabFactory.h"

FDinoCustomizerDatabaseAppMode::FDinoCustomizerDatabaseAppMode(TSharedPtr<class FDinoCustomizerDatabaseEditorApp> InApp) : FApplicationMode(TEXT("DinoCustomizerDatabaseAppMode"))
{
	EditorApp = InApp;
	Tabs.RegisterFactory(MakeShareable(new FDinoCustomizerDatabasePrimaryTabFactory(InApp)));
	Tabs.RegisterFactory(MakeShareable(new FDinoCustomizerDatabaseStudioTabFactory(InApp)));

	TabLayout = FTabManager::NewLayout(TEXT("DinoCustomizerDatabaseAppMode_LayOut_V1"))
	->AddArea(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewStack()
			->AddTab(FName(TEXT("DataBase")), ETabState::OpenedTab)
			->AddTab(FName(TEXT("Studio")), ETabState::OpenedTab)
			)
		);
}

void FDinoCustomizerDatabaseAppMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	TSharedPtr<FDinoCustomizerDatabaseEditorApp> App = EditorApp.Pin();
	App->PushTabFactories(Tabs);
	FApplicationMode::RegisterTabFactories(InTabManager);
}

void FDinoCustomizerDatabaseAppMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void FDinoCustomizerDatabaseAppMode::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}
