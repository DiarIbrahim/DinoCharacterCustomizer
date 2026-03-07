#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UDinoCustomizerSubDomain;
class UDinoCustomizerAction;

DECLARE_DELEGATE_OneParam(FOnDinoActionSelected, UDinoCustomizerSubDomain*);
DECLARE_DELEGATE_OneParam(FOnDinoActionDeleted, UDinoCustomizerSubDomain*);
DECLARE_DELEGATE_OneParam(FOnDinoActionDuplicated, UDinoCustomizerSubDomain*); 

class SInstanceSubDomainButton : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SInstanceSubDomainButton) {}
	SLATE_ARGUMENT(UDinoCustomizerSubDomain*, SubDomain)
		SLATE_ARGUMENT(bool, IsSelected)
	SLATE_EVENT(FOnDinoActionSelected, OnSelected)
	SLATE_EVENT(FOnDinoActionDeleted, OnDeleted)
	SLATE_EVENT(FOnDinoActionDuplicated, OnDuplicated)
 SLATE_END_ARGS()

 void Construct(const FArguments& InArgs);

	void SetIsSelected(bool InSelected);

	TWeakObjectPtr<UDinoCustomizerSubDomain> InstanceSubDomain = nullptr;
    
private:

	FOnDinoActionSelected OnSelectedDelegate;
	FOnDinoActionDeleted OnDeletedDelegate;
	FOnDinoActionDuplicated OnDuplicatedDelegate; 

	bool bSelected = false;

	TSharedPtr<FSlateImageBrush> ActionBrush;
	bool bHasValidBrush = false;

private:

	FReply OnDeleteClicked();
	FReply OnDuplicateClicked();
	FReply OnClicked();
};