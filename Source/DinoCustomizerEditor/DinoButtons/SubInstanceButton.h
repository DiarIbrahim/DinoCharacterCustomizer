#pragma once

#include "CoreMinimal.h"
#include "DinoListButton.h"
#include "DinoCustomizer/Actions/SubDomain/DinoCustomizerSubAction.h"
#include "Widgets/SCompoundWidget.h"

class UDinoCustomizerSubDomain;
class UDinoCustomizerAction;

DECLARE_DELEGATE_OneParam(FOnDinoSubActionSelected, UDinoCustomizerSubAction*);
DECLARE_DELEGATE_OneParam(FOnDinoSubActionDeleted, UDinoCustomizerSubAction*);
DECLARE_DELEGATE_OneParam(FOnDinoSubActionDuplicated, UDinoCustomizerSubAction*); 

class SSubInstanceButton : public SDinoListButton
{
public:

	void Construct(const FArguments& InArgs)
	{
		SDinoListButton::Construct(InArgs);
	}

	virtual void OnObjectSet(UObject* InObj) override;
	virtual TSharedRef<SWidget> GetButtonContent() override;

	TWeakObjectPtr<UDinoCustomizerSubAction> SubInstance = nullptr;

	TSharedPtr<FSlateImageBrush> ActionBrush;
	bool bHasValidBrush = false;

};