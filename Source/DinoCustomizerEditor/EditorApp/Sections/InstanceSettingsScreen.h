// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"
#include "Widgets/SCompoundWidget.h"

class SInstanceSubDomainButton;
class UDinoCustomizerDatabase;
class FDinoCustomizerDatabaseEditorApp;
class SDinoDomainButton;

DECLARE_DELEGATE_OneParam(FOnSubDomainDelegate, UDinoCustomizerSubDomain*);

class SInstanceSettingsScreen : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SInstanceSettingsScreen) {}
	SLATE_ARGUMENT(TWeakObjectPtr<UDinoCustomizerDatabase>, Database)
	SLATE_ARGUMENT(TWeakObjectPtr<UDinoCustomizerAction>, Action)
	SLATE_ATTRIBUTE(FLinearColor, DomainColor)
	SLATE_EVENT(FOnSubDomainDelegate, OnSubDomainSelected)
	SLATE_EVENT(FOnSubDomainDelegate, OnSubDomainDeleted)

		
SLATE_END_ARGS()

void Construct(const FArguments& InArgs);

	void SetInstance(UDinoCustomizerAction* InActionInstance);


	void RebuildSubDomains();
	TWeakObjectPtr<UDinoCustomizerSubDomain> SelectedSubDomain;

	

private:

	float SubDomainButtonHeight = 65.0f;

	FReply OnAddSubDomainClicked();
	void OnSubDomainSelected(UObject* InSubDomainObj);
	void OnSubDomainDuplicated(UObject* InSubDomainObj);
	void OnSubDomainDeleted(UObject* InSubDomainObj);
	void OnSubDomainMoveDown(UObject* InSubDomainObj);
	void OnSubDomainMoveUp(UObject* InSubDomainObj);
	
	// Incoming
	TWeakObjectPtr<UDinoCustomizerDatabase> Database;
	TWeakObjectPtr<UDinoCustomizerAction> CurrentInstance;
	TAttribute<FLinearColor> DomainColor;

	FOnSubDomainDelegate OnInstanceSelectedDelegate;
	FOnSubDomainDelegate OnInstanceDeletedDelegate;

	// Internal state
	TSharedPtr<SScrollBox> SubDomainScrollBox;
	
	TArray<TSharedPtr<SInstanceSubDomainButton>> SubDomainButtons;

	// Details 
	mutable TSharedPtr<IDetailsView> DetailsView;

};