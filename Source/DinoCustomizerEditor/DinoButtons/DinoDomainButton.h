#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UDinoCustomizerDatabaseDomain;

DECLARE_DELEGATE_OneParam(FOnDinoDomainClicked, UDinoCustomizerDatabaseDomain*)

class SDinoDomainButton : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SDinoDomainButton)
		: _Domain(nullptr)
		, _Height(90.f)
		, _IsSelected(false)
	{}
	SLATE_ARGUMENT(UDinoCustomizerDatabaseDomain*, Domain)
	SLATE_ARGUMENT(float, Height)
	SLATE_ARGUMENT(int32, DomainIndex)
	SLATE_ARGUMENT(int32, NumDomains)
	SLATE_ARGUMENT(bool, IsSelected)

	SLATE_EVENT(FOnDinoDomainClicked, OnClicked)
	SLATE_EVENT(FOnDinoDomainClicked, OnDeleteClicked)


	SLATE_EVENT(FOnDinoDomainClicked, OnMoveUpClicked)
	SLATE_EVENT(FOnDinoDomainClicked, OnMoveDownClicked)

SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void SetSelected(bool bSelected);
	UDinoCustomizerDatabaseDomain* GetDomain() const { return Domain; }

private:

	FReply HandleClicked();
	FReply HandleDeleteClicked();

	// NEW
	FReply HandleMoveUpClicked();
	FReply HandleMoveDownClicked();

	const FSlateBrush* GetBorderBrush() const;

private:

	UDinoCustomizerDatabaseDomain* Domain = nullptr;

	float Height = 90.f;
	bool bIsSelected = false;

	TSharedPtr<SBorder> OuterBorder;

	FOnDinoDomainClicked OnClicked;
	FOnDinoDomainClicked OnDeleteClicked;

	// NEW
	FOnDinoDomainClicked OnMoveUpClicked;
	FOnDinoDomainClicked OnMoveDownClicked;
};