#include "SubInstanceButton.h" // Ensure this matches your filename
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SImage.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizerEditor/Helpers/DinoCustomizerEditorHelper.h"

void SSubInstanceButton::Construct(const FArguments& InArgs)
{
	SubInstance = InArgs._SubInstance;
	OnSelectedDelegate = InArgs._OnSelected;
	OnDeletedDelegate = InArgs._OnDeleted;
	OnDuplicatedDelegate = InArgs._OnDuplicated;
	bSelected = InArgs._IsSelected;
	
	
	FSlateFontInfo NameFont = FAppStyle::GetFontStyle("PropertyWindow.BoldFont");
	NameFont.Size = 13;

	ChildSlot
	[

		SNew(SBorder)
		.BorderImage_Lambda([this]()
		{
			return bSelected
				       ? FAppStyle::GetBrush("FocusRectangle")
				       : FAppStyle::GetBrush("NoBorder");
		})

		[
			SNew(SButton)
			.ButtonStyle(FAppStyle::Get(), "Button")
			.OnClicked(this, &SSubInstanceButton::OnClicked)
			.ContentPadding(FMargin(4))
			[

				SNew(SBox)
				.HeightOverride(35)
				[
					SNew(SHorizontalBox)
					
					// TEXT SLOT
					+ SHorizontalBox::Slot()
					.FillWidth(1.f)
					.VAlign(VAlign_Center)
					.Padding(6, 0)
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot().AutoHeight()
						[
							SNew(STextBlock)
							.ColorAndOpacity(FLinearColor::White)
							.Font(NameFont)
							.Text_Lambda([this]()
							{
								return (SubInstance.IsValid() && !SubInstance->SubInstanceDisplayName.IsEmpty())
									       ? SubInstance->SubInstanceDisplayName
									       : FText::FromString("*");
							})
						]
						+ SVerticalBox::Slot().AutoHeight()
						[
							SNew(STextBlock)
							.Text_Lambda([this]()
							{
								return SubInstance.IsValid()
									       ? FText::Format(FText::FromString("Sub Instance Tag : {0}"),TAG_TEXT(SubInstance->SubInstanceTag))
									       : FText::GetEmpty();
							})
							.ColorAndOpacity(FLinearColor(0.3f, 0.7f, 1.0f))
						]
					]

					// NEW: DUPLICATE BUTTON
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(2, 0)
					[
						SNew(SButton)
						.ButtonStyle(FAppStyle::Get(), "SimpleButton")
						.ToolTipText(FText::FromString("Duplicate this action"))
						.OnClicked(this, &SSubInstanceButton::OnDuplicateClicked)
						[
							SNew(SImage)
							.Image(FAppStyle::GetBrush("Icons.Duplicate"))
							.ColorAndOpacity(FLinearColor(0.8f, 0.8f, 0.8f, 1.0f)) // Slightly dimmed until hover
						]
					]

					// DELETE BUTTON
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(2, 0)
					[
						SNew(SButton)
						.ButtonStyle(FAppStyle::Get(), "SimpleButton")
						.ToolTipText(FText::FromString("Delete this action"))
						.OnClicked(this, &SSubInstanceButton::OnDeleteClicked)
						[
							SNew(SImage)
							.Image(FAppStyle::GetBrush("Icons.Delete"))
						]
					]
				]
			]
		]
	];
}

void SSubInstanceButton::SetIsSelected(bool InSelected)
{
	bSelected = InSelected;
}

FReply SSubInstanceButton::OnDuplicateClicked()
{
	if (OnDuplicatedDelegate.IsBound())
	{
		OnDuplicatedDelegate.Execute(SubInstance.Get());
	}
	return FReply::Handled();
}

// ... (Existing OnClicked and OnDeleteClicked functions) ...

FReply SSubInstanceButton::OnClicked()
{
	bSelected = true;

	if (OnSelectedDelegate.IsBound()) { OnSelectedDelegate.Execute(SubInstance.Get()); }
	return FReply::Handled();
}

FReply SSubInstanceButton::OnDeleteClicked()
{
	if (OnDeletedDelegate.IsBound()) { OnDeletedDelegate.Execute(SubInstance.Get()); }
	return FReply::Handled();
}
