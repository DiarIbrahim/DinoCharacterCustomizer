#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UDinoCustomizerAction;

DECLARE_DELEGATE_OneParam(FOnDinoActionSelected, UDinoCustomizerAction*);
DECLARE_DELEGATE_OneParam(FOnDinoActionDeleted, UDinoCustomizerAction*);
DECLARE_DELEGATE_OneParam(FOnDinoActionDuplicated, UDinoCustomizerAction*); // New Delegate

class SDinoDomainInstanceActionButton : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SDinoDomainInstanceActionButton) {}
	SLATE_ARGUMENT(UDinoCustomizerAction*, Action)
	SLATE_ARGUMENT(bool, IsSelected)
	SLATE_EVENT(FOnDinoActionSelected, OnSelected)
	SLATE_EVENT(FOnDinoActionDeleted, OnDeleted)
	SLATE_EVENT(FOnDinoActionDuplicated, OnDuplicated) // New Argument
 SLATE_END_ARGS()

 void Construct(const FArguments& InArgs);

	void SetSelected(bool InSelected);

	TWeakObjectPtr<UDinoCustomizerAction> ActionInstance = nullptr;
    
private:

	FOnDinoActionSelected OnSelectedDelegate;
	FOnDinoActionDeleted OnDeletedDelegate;
	FOnDinoActionDuplicated OnDuplicatedDelegate; // New Member

	bool bSelected = false;

	TSharedPtr<FSlateImageBrush> ActionBrush;
	bool bHasValidBrush = false;

private:

	FReply OnDeleteClicked();
	FReply OnDuplicateClicked(); // New Handler
	FReply OnClicked();
};