#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizer/Actions/SubDomain/DinoCustomizerSubAction.h"
#include "Widgets/SCompoundWidget.h"

class UDinoCustomizerSubDomain;
class UDinoCustomizerAction;

DECLARE_DELEGATE_OneParam(FOnDinoSubActionSelected, UDinoCustomizerSubAction*);
DECLARE_DELEGATE_OneParam(FOnDinoSubActionDeleted, UDinoCustomizerSubAction*);
DECLARE_DELEGATE_OneParam(FOnDinoSubActionDuplicated, UDinoCustomizerSubAction*); 

class SSubInstanceButton : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SSubInstanceButton) {}
	SLATE_ARGUMENT(UDinoCustomizerSubAction*, SubInstance)
		SLATE_ARGUMENT(bool, IsSelected)

	SLATE_EVENT(FOnDinoSubActionSelected, OnSelected)
	SLATE_EVENT(FOnDinoSubActionDeleted, OnDeleted)
	SLATE_EVENT(FOnDinoSubActionDuplicated, OnDuplicated)
 SLATE_END_ARGS()

 void Construct(const FArguments& InArgs);

	void SetIsSelected(bool InSelected);

	TWeakObjectPtr<UDinoCustomizerSubAction> SubInstance = nullptr;
    
private:

	FOnDinoSubActionSelected OnSelectedDelegate;
	FOnDinoSubActionDeleted OnDeletedDelegate;
	FOnDinoSubActionDuplicated OnDuplicatedDelegate; 

	bool bSelected = false;

	TSharedPtr<FSlateImageBrush> ActionBrush;
	bool bHasValidBrush = false;

private:

	FReply OnDeleteClicked();
	FReply OnDuplicateClicked();
	FReply OnClicked();
};