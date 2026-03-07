#pragma once

#include "CoreMinimal.h"
#include "DinoListButton.h"
#include "Widgets/SCompoundWidget.h"

class UDinoCustomizerSubDomain;
class UDinoCustomizerAction;

DECLARE_DELEGATE_OneParam(FOnDinoActionSelected, UDinoCustomizerSubDomain*);
DECLARE_DELEGATE_OneParam(FOnDinoActionDeleted, UDinoCustomizerSubDomain*);
DECLARE_DELEGATE_OneParam(FOnDinoActionDuplicated, UDinoCustomizerSubDomain*); 

class SInstanceSubDomainButton : public SDinoListButton
{
public:
	
 void Construct(const FArguments& InArgs)
	{
		SDinoListButton::Construct(InArgs);
	}


	TWeakObjectPtr<UDinoCustomizerSubDomain> InstanceSubDomain = nullptr;

	virtual TSharedRef<SWidget> GetButtonContent() override;
	virtual void OnObjectSet(UObject* InObj) override;
    

	
	TSharedPtr<FSlateImageBrush> ActionBrush;
	bool bHasValidBrush = false;
};