// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class  FDinoCustomizerDatabaseStudioTabFactory : public FWorkflowTabFactory
{
public:

	FDinoCustomizerDatabaseStudioTabFactory(TSharedPtr<class FDinoCustomizerDatabaseEditorApp> App);


	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;


	
	virtual TSharedRef<SWidget> StudioSettings()const;

private:

	TWeakObjectPtr<UDinoCustomizerDatabase> Database;
	TWeakPtr<class FDinoCustomizerDatabaseEditorApp> EditorApp;

	mutable TSharedPtr<IDetailsView> DetailsView;
	
};
