// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerDatabaseStudioTabFactory.h"

#include "AssetThumbnail.h"
#include "DinoCustomizerDatabaseEditorApp.h"

#include "Widgets/Layout/SSeparator.h"
#include "Styling/AppStyle.h"

FDinoCustomizerDatabaseStudioTabFactory::FDinoCustomizerDatabaseStudioTabFactory(
	TSharedPtr<FDinoCustomizerDatabaseEditorApp> App) : FWorkflowTabFactory(FName("Studio"), App)
{
	EditorApp = App;
	TabLabel = FText::FromString("Studio");
	ViewMenuDescription = FText::FromString("Studio View Menu");
	ViewMenuTooltip = FText::FromString("Show Studio View Menu");

	Database = App->DataBase;
    
}

TSharedRef<SWidget> FDinoCustomizerDatabaseStudioTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(.15)
		[
			SNew(SBox)
			.HeightOverride(120)
			[
				StudioSettings()
			]

		
		];
}

FText FDinoCustomizerDatabaseStudioTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString("Studio Tab Tool tip");
}

TSharedRef<SWidget> FDinoCustomizerDatabaseStudioTabFactory::StudioSettings() const
{
	FPropertyEditorModule& PropertyModule =
	FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bHideSelectionTip = true;
	DetailsViewArgs.bAllowSearch = false;
	DetailsViewArgs.bShowOptions = false;
	//DetailsViewArgs.

	// Create details view (this returns a TSharedRef)
	DetailsView = PropertyModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(Database.Get());

	return  DetailsView.ToSharedRef();
}

