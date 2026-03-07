#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_OneParam(FOnDinoListButtonClicked, UObject*)

class SDinoListButton : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SDinoListButton)
		: _Object(nullptr)
		, _Height(90.f)
		, _IsSelected(false)
	{}
	SLATE_ARGUMENT(UObject*, Object)
	SLATE_ARGUMENT(float, Height)
	SLATE_ARGUMENT(int32, ItemIndex)
	SLATE_ARGUMENT(int32, NumItems)
	SLATE_ARGUMENT(bool, IsSelected)
	SLATE_ATTRIBUTE(FLinearColor, Color)


	SLATE_EVENT(FOnDinoListButtonClicked, OnClicked)
	SLATE_EVENT(FOnDinoListButtonClicked, OnDeleteClicked)
	SLATE_EVENT(FOnDinoListButtonClicked, OnDuplicateClicked)
	SLATE_EVENT(FOnDinoListButtonClicked, OnMoveUpClicked)
	SLATE_EVENT(FOnDinoListButtonClicked, OnMoveDownClicked)


SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void SetSelected(bool bSelected);

	virtual void OnObjectSet(UObject* InObj);
	
	UObject* GetObject() const { return Object; }
	virtual TSharedRef<SWidget> GetButtonContent();
	virtual FLinearColor GetButtonColor();


private:

	FReply HandleClicked();
	FReply HandleDeleteClicked();
	FReply HandleDuplicate();

	FReply HandleMoveUpClicked();
	FReply HandleMoveDownClicked();

	const FSlateBrush* GetBorderBrush() const;

private:

	UObject* Object = nullptr;
	TAttribute<FLinearColor> Color = FLinearColor::White;
	float Height = 90.f;
	bool bIsSelected = false;

	TSharedPtr<SBorder> OuterBorder;

	FOnDinoListButtonClicked OnClicked;
	FOnDinoListButtonClicked OnDeleteClicked;
	FOnDinoListButtonClicked OnDuplicateClicked;
	FOnDinoListButtonClicked OnMoveUpClicked;
	FOnDinoListButtonClicked OnMoveDownClicked;
};