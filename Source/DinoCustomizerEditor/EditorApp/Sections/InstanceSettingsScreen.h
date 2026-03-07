// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"
#include "Widgets/SCompoundWidget.h"

class SInstanceSubDomainButton;
class UDinoCustomizerDatabase;
class UDinoCustomizableDatabaseDomain;
class FDinoCustomizerDatabaseEditorApp;
class SDinoDomainButton;

DECLARE_DELEGATE_OneParam(FOnSubDomainDelegate, UDinoCustomizerSubDomain*);

class SInstanceSettingsScreen : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SInstanceSettingsScreen) {}
	SLATE_ARGUMENT(TWeakObjectPtr<UDinoCustomizerDatabase>, Database)
	SLATE_ARGUMENT(TWeakObjectPtr<UDinoCustomizerAction>, Action)
	SLATE_EVENT(FOnSubDomainDelegate, OnSubDomainSelected)
	SLATE_EVENT(FOnSubDomainDelegate, OnSubDomainDeleted)

		
SLATE_END_ARGS()

void Construct(const FArguments& InArgs);

	void SetInstance(UDinoCustomizerAction* InActionInstance);

	void RebuildSubDomains();
	TWeakObjectPtr<UDinoCustomizerSubDomain> SelectedSubDomain;

	

private:


	FReply OnAddSubDomainClicked();
	void OnSubDomainSelected(UDinoCustomizerSubDomain* DinoCustomizerSubDomain);
	void OnSubDomainDuplicated(UDinoCustomizerSubDomain* DinoCustomizerSubDomain);
	void OnSubDomainDeleted(UDinoCustomizerSubDomain* DinoCustomizerSubDomain);

	
	// Incoming
	TWeakObjectPtr<UDinoCustomizerDatabase> Database;
	TWeakObjectPtr<UDinoCustomizerAction> CurrentInstance;

	FOnSubDomainDelegate OnInstanceSelectedDelegate;
	FOnSubDomainDelegate OnInstanceDeletedDelegate;

	// Internal state
	TSharedPtr<SScrollBox> SubDomainScrollBox;
	
	TArray<TSharedPtr<SInstanceSubDomainButton>> SubDomainButtons;

	// Details 
	mutable TSharedPtr<IDetailsView> DetailsView;

};