// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"


class  FDinoCustomizerDatabaseAppMode : public FApplicationMode
{

public:
	FDinoCustomizerDatabaseAppMode(TSharedPtr<class FDinoCustomizerDatabaseEditorApp> InApp);

	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;


private:

	TWeakPtr<class FDinoCustomizerDatabaseEditorApp> EditorApp;
	FWorkflowAllowedTabSet Tabs;
	
};
