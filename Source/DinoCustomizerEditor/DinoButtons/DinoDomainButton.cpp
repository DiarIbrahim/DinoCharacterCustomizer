#include "DinoDomainButton.h"

#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"
#include "DinoCustomizerEditor/Helpers/DinoCustomizerEditorHelper.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Images/SImage.h"
#include "Styling/AppStyle.h"
#include "Windows/WindowsApplication.h"

// void SDinoDomainButton::Construct(const FArguments& InArgs)
// {
// 	SDinoListButton::Construct(InArgs);
// 	
// 	OnClicked = InArgs._OnClicked;
// 	OnDeleteClicked = InArgs._OnDeleteClicked;
// 	OnMoveUpClicked = InArgs._OnMoveUpClicked;
// 	OnMoveDownClicked = InArgs._OnMoveDownClicked;
// 	//
// 	// ChildSlot
// 	// [
// 	// 	SNew(SBox)
// 	// 	.HeightOverride(Height)
// 	// 	[
// 	// 		SAssignNew(OuterBorder, SBorder)
// 	// 		.BorderImage(this, &SDinoDomainButton::GetBorderBrush)
// 	// 		.BorderBackgroundColor_Lambda([this]() { return Domain->DomainColor; })
// 	// 		.Padding(2)
// 	// 		[
// 	// 			SNew(SButton)
// 	// 			.ButtonColorAndOpacity_Lambda([this]() { return Domain->DomainColor; })
// 	// 			.OnClicked(this, &SDinoDomainButton::HandleClicked)
// 	// 			.ContentPadding(FMargin(2.0f, 8.0f, 12.0f,8.0f))
// 	// 			[
// 	// 				SNew(SHorizontalBox)
// 	//
// 	// 				// --- NEW: Left Column Move Buttons ---
// 	// 				+ SHorizontalBox::Slot()
// 	// 				.AutoWidth()
// 	// 				.VAlign(VAlign_Center)
// 	// 				.Padding(0,0,8,0)
// 	// 				[
// 	// 					SNew(SVerticalBox)
// 	//
// 	// 					+ SVerticalBox::Slot()
// 	// 					.AutoHeight()
// 	// 					[
// 	// 						SNew(SButton)
// 	// 						.IsEnabled(bSHowOrderUpButton)
// 	// 						.ButtonStyle(FAppStyle::Get(), "SimpleButton")
// 	// 						.OnClicked(this, &SDinoDomainButton::HandleMoveUpClicked)
// 	// 						.ToolTipText(FText::FromString("Move Up"))
// 	// 						.ContentPadding(4)
// 	// 						[
// 	// 							SNew(SImage)
// 	// 							.Image(FAppStyle::GetBrush("Icons.ChevronUp"))
// 	// 							.DesiredSizeOverride(FVector2D(12,12))
// 	// 						]
// 	// 					]
// 	// 					
// 	// 					+ SVerticalBox::Slot()
// 	// 					[
// 	// 						SNew(SSpacer)
// 	// 						.Size(FVector2D(0,10))
// 	// 					]
// 	//
// 	// 					
// 	// 					+ SVerticalBox::Slot()
// 	// 					.AutoHeight()
// 	// 					[
// 	// 						SNew(SButton)
// 	// 						.IsEnabled(bSHowOrderDownButton)
// 	// 						.ButtonStyle(FAppStyle::Get(), "SimpleButton")
// 	// 						.OnClicked(this, &SDinoDomainButton::HandleMoveDownClicked)
// 	// 						.ToolTipText(FText::FromString("Move Down"))
// 	// 						.ContentPadding(4)
// 	// 						[
// 	// 							SNew(SImage)
// 	// 							.Image(FAppStyle::GetBrush("Icons.ChevronDown"))
// 	// 							.DesiredSizeOverride(FVector2D(12,12))
// 	// 						]
// 	// 					]
// 	// 				]
// 	//
// 	// 				// --- Left Column: Stacked Text Data ---
// 	// 				+ SHorizontalBox::Slot()
// 	// 				.FillWidth(1.f)
// 	// 				.VAlign(VAlign_Center)
// 	// 				[
// 	// 					
// 	// 				]
// 	//
// 	// 				// --- Right Column: Delete Button ---
// 	// 				+ SHorizontalBox::Slot()
// 	// 				.AutoWidth()
// 	// 				.VAlign(VAlign_Center)
// 	// 				.Padding(8, 0, 0, 0)
// 	// 				[
// 	// 					SNew(SButton)
// 	// 					.ButtonStyle(FAppStyle::Get(), "SimpleButton")
// 	// 					.OnClicked(this, &SDinoDomainButton::HandleDeleteClicked)
// 	// 					.ContentPadding(4)
// 	// 					.ToolTipText(FText::FromString("Delete Domain"))
// 	// 					[
// 	// 						SNew(SImage)
// 	// 						.Image(FAppStyle::GetBrush("Icons.Delete"))
// 	// 						.DesiredSizeOverride(FVector2D(16, 16))
// 	// 						.ColorAndOpacity(FSlateColor::UseForeground())
// 	// 					]
// 	// 				]
// 	// 			]
// 	// 		]
// 	// 	]
// 	// ];
// }

TSharedRef<SWidget> SDinoDomainButton::GetButtonContent()
{
	
	FSlateFontInfo TitleFont = FAppStyle::GetFontStyle("PropertyWindow.BoldFont");
	TitleFont.Size = 16; 

	return SNew(SVerticalBox)

						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(0, 0, 0, 4)
						[
							SNew(STextBlock)
							.Font(TitleFont)
							.Text_Lambda([this]()
							{
								return IsValid(Domain) ? Domain->GetDomainDisplayName() : FText::FromString("Invalid Domain");
							})
						]

						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(0, 0, 0, 4)
						[
							SNew(STextBlock)
							.ColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.8f, 0.0f)))
							.Text_Lambda([this]()
							{
								int32 NumInstances = Domain->Instances.Num();
								return FText::FormatOrdered(FText::FromString("Number Of Instances : {0}"),NumInstances);
							})
						]

						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(STextBlock)
							.ColorAndOpacity(FSlateColor(FLinearColor(0.3f, 0.6f, 1.0f)))
							.Text_Lambda([this]()
							{
								return FText::FormatOrdered(FText::FromString("Domain : {0}"), DinoHelper::TAG_TEXT(Domain->DomainTag));
							})
						];
}

void SDinoDomainButton::OnObjectSet(UObject* InObj)
{
	SDinoListButton::OnObjectSet(InObj);
	Domain = Cast<UDinoCustomizerDatabaseDomain>(InObj);
}

FLinearColor SDinoDomainButton::GetButtonColor()
{
	return Domain->DomainColor;
}

//
// FReply SDinoDomainButton::HandleClicked()
// {
// 	if (OnClicked.IsBound())
// 	{
// 		OnClicked.Execute(Domain);
// 	}
// 	return FReply::Handled();
// }
//
// FReply SDinoDomainButton::HandleDeleteClicked()
// {
// 	if (OnDeleteClicked.IsBound())
// 	{
// 		OnDeleteClicked.Execute(Domain);
// 	}
// 	return FReply::Handled();
// }
//
// FReply SDinoDomainButton::HandleMoveUpClicked()
// {
// 	if (OnMoveUpClicked.IsBound())
// 	{
// 		OnMoveUpClicked.Execute(Domain);
// 	}
// 	return FReply::Handled();
// }
//
// FReply SDinoDomainButton::HandleMoveDownClicked()
// {
// 	if (OnMoveDownClicked.IsBound())
// 	{
// 		OnMoveDownClicked.Execute(Domain);
// 	}
// 	return FReply::Handled();
// }