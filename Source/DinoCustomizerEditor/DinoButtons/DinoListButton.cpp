#include "DinoListButton.h"

#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"
#include "DinoCustomizerEditor/Helpers/DinoCustomizerEditorHelper.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Images/SImage.h"
#include "Styling/AppStyle.h"
#include "Windows/WindowsApplication.h"

void SDinoListButton::Construct(const FArguments& InArgs)
{
	Object = InArgs._Object;
	Height = InArgs._Height;
	bIsSelected = InArgs._IsSelected;
	OnClicked = InArgs._OnClicked;
	OnDeleteClicked = InArgs._OnDeleteClicked;
	OnMoveUpClicked = InArgs._OnMoveUpClicked;
	OnMoveDownClicked = InArgs._OnMoveDownClicked;

	bool bSHowOrderUpButton = InArgs._ItemIndex != 0;
	bool bSHowOrderDownButton = InArgs._ItemIndex != InArgs._NumItems-1;

	FSlateFontInfo TitleFont = FAppStyle::GetFontStyle("PropertyWindow.BoldFont");
	TitleFont.Size = 16; 

	ChildSlot
	[
		SNew(SBox)
		.HeightOverride(Height)
		[
			SAssignNew(OuterBorder, SBorder)
			.BorderImage(this, &SDinoListButton::GetBorderBrush)
			.BorderBackgroundColor_Lambda([this]() { return GetButtonColor(); })
			.Padding(2)
			[
				SNew(SButton)
				.ButtonColorAndOpacity_Lambda([this]() { return GetButtonColor(); })
				.OnClicked(this, &SDinoListButton::HandleClicked)
				.ContentPadding(FMargin(2.0f, 8.0f, 12.0f,8.0f))
				[
					SNew(SHorizontalBox)

					// --- NEW: Left Column Move Buttons ---
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(0,0,8,0)
					[
						SNew(SVerticalBox)

						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SButton)
							.IsEnabled(bSHowOrderUpButton)
							.ButtonStyle(FAppStyle::Get(), "SimpleButton")
							.OnClicked(this, &SDinoListButton::HandleMoveUpClicked)
							.ToolTipText(FText::FromString("Move Up"))
							.ContentPadding(4)
							[
								SNew(SImage)
								.Image(FAppStyle::GetBrush("Icons.ChevronUp"))
								.DesiredSizeOverride(FVector2D(12,12))
							]
						]
						
						+ SVerticalBox::Slot()
						.FillHeight(1)
						[
							SNew(SSpacer)
						]

						
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SButton)
							.IsEnabled(bSHowOrderDownButton)
							.ButtonStyle(FAppStyle::Get(), "SimpleButton")
							.OnClicked(this, &SDinoListButton::HandleMoveDownClicked)
							.ToolTipText(FText::FromString("Move Down"))
							.ContentPadding(4)
							[
								SNew(SImage)
								.Image(FAppStyle::GetBrush("Icons.ChevronDown"))
								.DesiredSizeOverride(FVector2D(12,12))
							]
						]
					]

					+ SHorizontalBox::Slot()
					.FillWidth(1)
					[
						GetButtonContent()
					]

					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(2, 0)
					[
						SNew(SButton)
						.ButtonStyle(FAppStyle::Get(), "SimpleButton")
						.ToolTipText(FText::FromString("Duplicate this action"))
						.OnClicked(this, &SDinoListButton::HandleDuplicate)
						[
							SNew(SImage)
							.Image(FAppStyle::GetBrush("Icons.Duplicate"))
							.ColorAndOpacity(FLinearColor(0.8f, 0.8f, 0.8f, 1.0f)) // Slightly dimmed until hover
						]
					]

					// --- Right Column: Delete Button ---
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(8, 0, 0, 0)
					[
						SNew(SButton)
						.ButtonStyle(FAppStyle::Get(), "SimpleButton")
						.OnClicked(this, &SDinoListButton::HandleDeleteClicked)
						.ContentPadding(4)
						.ToolTipText(FText::FromString("Delete Object"))
						[
							SNew(SImage)
							.Image(FAppStyle::GetBrush("Icons.Delete"))
							.DesiredSizeOverride(FVector2D(16, 16))
							.ColorAndOpacity(FSlateColor::UseForeground())
						]
					]
				]
			]
		]
	];
}

void SDinoListButton::SetSelected(bool bSelected)
{
	bIsSelected = bSelected;

	if (OuterBorder.IsValid())
	{
		OuterBorder->Invalidate(EInvalidateWidget::LayoutAndVolatility);
	}
}

const FSlateBrush* SDinoListButton::GetBorderBrush() const
{
	return bIsSelected
		? FAppStyle::GetBrush("FocusRectangle")
		: FAppStyle::GetBrush("NoBorder");
}

TSharedRef<SWidget> SDinoListButton::GetButtonContent()
{
	return SNew(SOverlay)

		+SOverlay::Slot()
		[
			SNew(SImage)
		.ColorAndOpacity(FColor::Red)
		]

	+SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
		.ColorAndOpacity(FColor::White)
			.Text(FText::FromString(" Button Content "))
		];
}

FColor SDinoListButton::GetButtonColor()
{
	return FColor::White;
}

FReply SDinoListButton::HandleClicked()
{
	if (OnClicked.IsBound())
	{
		OnClicked.Execute(Object);
	}
	return FReply::Handled();
}

FReply SDinoListButton::HandleDeleteClicked()
{
	if (OnDeleteClicked.IsBound())
	{
		OnDeleteClicked.Execute(Object);
	}
	return FReply::Handled();
}

FReply SDinoListButton::HandleDuplicate()
{
	return FReply::Handled();
}

FReply SDinoListButton::HandleMoveUpClicked()
{
	if (OnMoveUpClicked.IsBound())
	{
		OnMoveUpClicked.Execute(Object);
	}
	return FReply::Handled();
}

FReply SDinoListButton::HandleMoveDownClicked()
{
	if (OnMoveDownClicked.IsBound())
	{
		OnMoveDownClicked.Execute(Object);
	}
	return FReply::Handled();
}