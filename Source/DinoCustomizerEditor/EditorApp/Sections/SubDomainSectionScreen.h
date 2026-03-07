// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "InstanceSettingsScreen.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"
#include "Widgets/SCompoundWidget.h"

class SSubInstanceButton;
class SInstanceSubDomainButton;
class UDinoCustomizerDatabase;
class FDinoCustomizerDatabaseEditorApp;
class SDinoDomainButton;

DECLARE_DELEGATE_OneParam(FOnSubInstanceDelegate, UDinoCustomizerSubAction*);

class SSubDomainSectionScreen : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SSubDomainSectionScreen) {}
	SLATE_ARGUMENT(TWeakObjectPtr<UDinoCustomizerDatabase>, Database)
	SLATE_ARGUMENT(TWeakObjectPtr<UDinoCustomizerSubDomain>, SubDomain)
	SLATE_ATTRIBUTE(FLinearColor, DomainColor)
	SLATE_EVENT(FOnSubInstanceDelegate, OnSubInstanceSelected)
	SLATE_EVENT(FOnSubInstanceDelegate, OnSubInstanceDeleted)

		
SLATE_END_ARGS()

void Construct(const FArguments& InArgs);

	void SetSubDomain(UDinoCustomizerSubDomain* InSubDomain);

	void RebuildSubInstances();

	TWeakObjectPtr<UDinoCustomizerSubAction> SelectedSubInstance;
	TAttribute<FLinearColor> DomainColor;
	float SubInstanceButtonHeight = 65.0f;

private:


	FReply OnAddSubInstanceClicked();
	void OnSubInstanceSelected(UObject* InSubInstanceObj);
	void OnSubInstanceDuplicated(UObject* InSubInstanceObj);
	void OnSubInstanceDeleted(UObject* InSubInstanceObj);
	void OnSubInstanceMoveUp(UObject* InSubInstanceObj);
	void OnSubInstanceMoveDown(UObject* InSubInstanceObj);


	
	// Incoming
	TWeakObjectPtr<UDinoCustomizerDatabase> Database;
	TWeakObjectPtr<UDinoCustomizerSubDomain> CurrentSubDomain;


	FOnSubInstanceDelegate OnInstanceSelectedDelegate;
	FOnSubInstanceDelegate OnInstanceDeletedDelegate;


	// Internal state
	TSharedPtr<SScrollBox> SubDomainScrollBox;
	
	TArray<TSharedPtr<SSubInstanceButton>> SubInstanceButtons;

	// Details 
	mutable TSharedPtr<IDetailsView> DetailsView;

};