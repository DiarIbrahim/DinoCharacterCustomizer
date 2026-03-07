// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizerEditor/Other/Colors.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class FDinoCustomizerDatabaseEditorApp : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{
	public:

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	void OpenEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UObject* InObject);


	TWeakObjectPtr<class UDinoCustomizerDatabase> DataBase;

public: // asset editor tool kit

	virtual FName GetToolkitFName() const override{return FName("DinoCustomizerDatabaseEditor");}
	virtual FText GetBaseToolkitName() const override { return FText::FromString("Dino Customizer Database Editor");}
	virtual FString GetWorldCentricTabPrefix() const override {return FString("Dino Customizer Database Editor");}
	virtual FLinearColor GetWorldCentricTabColorScale() const override{return DinoColors::GetMainColor();}
	virtual FString GetDocumentationLink() const override {return "https://www.linkedin.com/in/diar-ibrahim-ali/";}
	virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override{}
	virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override{}

	
	
	
};
