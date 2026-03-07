// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"
#include "Widgets/SCompoundWidget.h"

class UDinoCustomizerDatabase;
class UDinoCustomizerDatabaseDomain;
class UDinoCustomizerAction;

DECLARE_DELEGATE_OneParam(FOnDomainInstanceDelegate, UDinoCustomizerAction*);

class SDomainContentSectionScreen : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SDomainContentSectionScreen) {}
	SLATE_ARGUMENT(TWeakObjectPtr<UDinoCustomizerDatabase>, Database)
	SLATE_ARGUMENT(TWeakObjectPtr<UDinoCustomizerDatabaseDomain>, Domain)
	SLATE_EVENT(FOnDomainInstanceDelegate, OnInstanceSelected)
	SLATE_EVENT(FOnDomainInstanceDelegate, OnInstanceDeleted)

SLATE_END_ARGS()

void Construct(const FArguments& InArgs);

	// ===== PUBLIC API =====

	void SetDomain(UDinoCustomizerDatabaseDomain* InDomain);
	void SetDatabase(UDinoCustomizerDatabase* InDatabase);
	void RebuildDomainContentWindow(); // Explicit rebuild allowed

private:
	void OnInstanceDeleted(UDinoCustomizerAction* DinoCustomizerAction);
	void OnInstanceDuplicated(UDinoCustomizerAction* DinoCustomizerAction);

	FReply OnAddInstanceClicked();
	void HandleInstanceSelected(UDinoCustomizerAction* Instance);
	
	// Data
	TWeakObjectPtr<UDinoCustomizerDatabase> Database;
	TWeakObjectPtr<UDinoCustomizerDatabaseDomain> SelectedDomain;
	TWeakObjectPtr<UDinoCustomizerAction> SelectedInstance;

	TArray<TSharedPtr<class SDinoDomainInstanceActionButton>> InstanceButtons;
	
	FOnDomainInstanceDelegate OnInstanceSelectedDelegate;
	FOnDomainInstanceDelegate OnInstanceDeletedDelegate;
	// UI
	TSharedPtr<SVerticalBox> DomainContentVerticalBox;

	TSharedPtr<IDetailsView> DetailsView;

private:

};