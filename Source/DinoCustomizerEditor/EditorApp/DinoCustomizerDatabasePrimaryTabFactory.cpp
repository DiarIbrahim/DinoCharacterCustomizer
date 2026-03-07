// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerDatabasePrimaryTabFactory.h"
#include "AssetThumbnail.h"
#include "DinoCustomizerDatabaseEditorApp.h"
#include "Sections/DomainSectionScreen.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "Sections/DinoCustomizerDatabaseEditorScreen.h"

FDinoCustomizerDatabasePrimaryTabFactory::FDinoCustomizerDatabasePrimaryTabFactory(
	TSharedPtr<FDinoCustomizerDatabaseEditorApp> App) : FWorkflowTabFactory(FName("DataBase"), App)
{
	EditorApp = App;
	TabLabel = FText::FromString("DataBase");
	ViewMenuDescription = FText::FromString("DataBase View Menu");
	ViewMenuTooltip = FText::FromString("Show DataBase View Menu");

	Database = App->DataBase;

}

TSharedRef<SWidget> FDinoCustomizerDatabasePrimaryTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{

	
	return
		SNew(SDinoCustomizerDatabaseEditorScreen)
		.Database(Database);
}

FText FDinoCustomizerDatabasePrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString("DataBase Tab Tool tip");
}


