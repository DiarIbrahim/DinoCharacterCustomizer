// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class  FDinoCustomizerDatabasePrimaryTabFactory : public FWorkflowTabFactory
{
public:

	FDinoCustomizerDatabasePrimaryTabFactory(TSharedPtr<class FDinoCustomizerDatabaseEditorApp> App);


	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;


private:

	TWeakObjectPtr<UDinoCustomizerDatabase> Database;
	TWeakPtr<class FDinoCustomizerDatabaseEditorApp> EditorApp;



};
