#pragma once

#include "CoreMinimal.h"
#include "DinoListButton.h"
#include "Widgets/SCompoundWidget.h"
#include "WorldPartition/WorldPartitionBuilder.h"

class UDinoCustomizerAction;

DECLARE_DELEGATE_OneParam(FOnDinoActionSelected, UDinoCustomizerAction*);
DECLARE_DELEGATE_OneParam(FOnDinoActionDeleted, UDinoCustomizerAction*);
DECLARE_DELEGATE_OneParam(FOnDinoActionDuplicated, UDinoCustomizerAction*); // New Delegate

class SDinoDomainInstanceActionButton : public SDinoListButton
{
public:


 void Construct(const FArguments& InArgs)
	{
 		SDinoListButton::Construct(InArgs);
	}

	virtual TSharedRef<SWidget> GetButtonContent() override;
	virtual void OnObjectSet(UObject* InObj) override;
	


	TWeakObjectPtr<UDinoCustomizerAction> ActionInstance = nullptr;
    
private:

	FOnDinoActionSelected OnSelectedDelegate;
	FOnDinoActionDeleted OnDeletedDelegate;
	FOnDinoActionDuplicated OnDuplicatedDelegate;


	TSharedPtr<FSlateImageBrush> ActionBrush;
	bool bHasValidBrush = false;


};