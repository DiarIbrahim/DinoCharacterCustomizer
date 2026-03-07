#pragma once

#include "CoreMinimal.h"
#include "DinoListButton.h"
#include "Widgets/SCompoundWidget.h"

class UDinoCustomizerDatabaseDomain;

DECLARE_DELEGATE_OneParam(FOnDinoDomainClicked, UDinoCustomizerDatabaseDomain*)

class SDinoDomainButton : public SDinoListButton
{
public:


	void Construct(const FArguments& InArgs)
	{
		SDinoListButton::Construct(InArgs);
	}

	virtual TSharedRef<SWidget> GetButtonContent() override;
	virtual void OnObjectSet(UObject* InObj) override;
	virtual FLinearColor GetButtonColor() override;
	
	UDinoCustomizerDatabaseDomain* GetDomain() const { return Domain; }

private:



private:

	UDinoCustomizerDatabaseDomain* Domain = nullptr;
	

	FOnDinoDomainClicked OnClicked;
	FOnDinoDomainClicked OnDeleteClicked;

	// NEW
	FOnDinoDomainClicked OnMoveUpClicked;
	FOnDinoDomainClicked OnMoveDownClicked;
};