#include "InstanceSubDomainButton.h" // Ensure this matches your filename
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SImage.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizerEditor/Helpers/DinoCustomizerEditorHelper.h"

void SInstanceSubDomainButton::Construct(const FArguments& InArgs)
{
	InstanceSubDomain = InArgs._SubDomain;
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
			.OnClicked(this, &SInstanceSubDomainButton::OnClicked)
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
								return (InstanceSubDomain.IsValid() && !InstanceSubDomain->SubDomainDisplayName.IsEmpty())
									       ? InstanceSubDomain->SubDomainDisplayName
									       : FText::FromString("*");
							})
						]
						+ SVerticalBox::Slot().AutoHeight()
						[
							SNew(STextBlock)
							.Text_Lambda([this]()
							{
								return InstanceSubDomain.IsValid()
									       ? FText::Format(FText::FromString("Sub Domain Tag : {0}"),TAG_TEXT(InstanceSubDomain->SubDomainTag))
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
						.OnClicked(this, &SInstanceSubDomainButton::OnDuplicateClicked)
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
						.OnClicked(this, &SInstanceSubDomainButton::OnDeleteClicked)
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

void SInstanceSubDomainButton::SetIsSelected(bool InSelected)
{
	bSelected = InSelected;
}


FReply SInstanceSubDomainButton::OnDuplicateClicked()
{
	if (OnDuplicatedDelegate.IsBound())
	{
		OnDuplicatedDelegate.Execute(InstanceSubDomain.Get());
	}
	return FReply::Handled();
}

// ... (Existing OnClicked and OnDeleteClicked functions) ...

FReply SInstanceSubDomainButton::OnClicked()
{
	bSelected = true;

	if (OnSelectedDelegate.IsBound()) { OnSelectedDelegate.Execute(InstanceSubDomain.Get()); }
	return FReply::Handled();
}

FReply SInstanceSubDomainButton::OnDeleteClicked()
{
	if (OnDeletedDelegate.IsBound()) { OnDeletedDelegate.Execute(InstanceSubDomain.Get()); }
	return FReply::Handled();
}
