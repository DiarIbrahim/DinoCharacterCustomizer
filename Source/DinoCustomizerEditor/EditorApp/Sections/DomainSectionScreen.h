// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"
#include "Widgets/SCompoundWidget.h"

class UDinoCustomizerDatabase;
class UDinoCustomizerDatabaseDomain;
class FDinoCustomizerDatabaseEditorApp;
class SDinoDomainButton;

DECLARE_DELEGATE_OneParam(FOnDomainDelegate, UDinoCustomizerDatabaseDomain*);
DECLARE_DELEGATE_OneParam(FOnDomainDelegate, UDinoCustomizerDatabaseDomain*);

class SDomainSectionScreen : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SDomainSectionScreen) {}
	SLATE_ARGUMENT(TWeakObjectPtr<UDinoCustomizerDatabase>, Database)
	SLATE_EVENT(FOnDomainDelegate, OnDomainSelected)
	SLATE_EVENT(FOnDomainDelegate, OnDomainDeleted)

SLATE_END_ARGS()

void Construct(const FArguments& InArgs);

private:

	// Incoming
	TWeakObjectPtr<UDinoCustomizerDatabase> Database;

	FOnDomainDelegate OnDomainSelectedDelegate;
	FOnDomainDelegate OnDomainDeletedDelegate;


	// Internal state
	TSharedPtr<SScrollBox> DomainsScrollBox;
	UDinoCustomizerDatabaseDomain* SelectedDomain = nullptr;
	TArray<TSharedPtr<SDinoDomainButton>> DomainButtons;

	float DomainButtonHeight = 90.0f;

private:

	void RebuildDomainsUI();
	FReply OnAddDomainClicked();
	void HandleDomainSelected(UObject* InDomainObj);
	void HandleDomainDuplicated(UObject* InDomainObj);
	void HandleDomainDeleted(UObject* InDomainObj);
	void MoveDomainOrderUp(UObject* InDomainObj);
	void MoveDomainOrderDown(UObject* InDomainObj);
};