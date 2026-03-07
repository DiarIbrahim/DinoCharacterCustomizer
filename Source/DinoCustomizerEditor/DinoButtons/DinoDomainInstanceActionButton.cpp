#include "DinoDomainInstanceActionButton.h" // Ensure this matches your filename
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SImage.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizerEditor/Helpers/DinoCustomizerEditorHelper.h"

void SDinoDomainInstanceActionButton::Construct(const FArguments& InArgs)
{
	ActionInstance = InArgs._Action;
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
			.OnClicked(this, &SDinoDomainInstanceActionButton::OnClicked)
			.ContentPadding(FMargin(4))
			[

				SNew(SBox)
				.HeightOverride(35)
				[
					SNew(SHorizontalBox)

					// IMAGE SLOT
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.WidthOverride(35)
						.HeightOverride(35)
						[
							SNew(SImage)
							.Visibility_Lambda([this]()
							{
								return ActionInstance.IsValid() && ActionInstance->ActionDisplayImage.IsValid()
									       ? EVisibility::Visible
									       : EVisibility::Hidden;
							})
							.Image_Lambda([this]() -> const FSlateBrush* {
								if (ActionInstance.IsValid() && !ActionInstance->ActionDisplayImage.IsNull())
								{
									UTexture2D* CurrentTexture = ActionInstance->ActionDisplayImage.Get();
									if (!CurrentTexture)
									{
										CurrentTexture = ActionInstance->ActionDisplayImage.LoadSynchronous();
									}

									if (CurrentTexture)
									{
										if (!ActionBrush.IsValid() || ActionBrush->GetResourceObject() !=
											CurrentTexture)
										{
											ActionBrush = MakeShared<FSlateImageBrush>(
												CurrentTexture, FVector2D(32, 32));
										}
										return ActionBrush.Get();
									}
								}
								return FAppStyle::GetBrush("Default");
							})
						]
					]

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
								return (ActionInstance.IsValid() && !ActionInstance->ActionDisplayName.IsEmpty())
									       ? ActionInstance->ActionDisplayName
									       : FText::FromString("*");
							})
						]
						+ SVerticalBox::Slot().AutoHeight()
						[
							SNew(STextBlock)
							.Text_Lambda([this]()
							{
								return ActionInstance.IsValid()
									       ? FText::Format(FText::FromString("Instance Tag : {0}"), TAG_TEXT(ActionInstance->InstanceTag))
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
						.OnClicked(this, &SDinoDomainInstanceActionButton::OnDuplicateClicked)
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
						.OnClicked(this, &SDinoDomainInstanceActionButton::OnDeleteClicked)
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

void SDinoDomainInstanceActionButton::SetSelected(bool InSelected)
{
	bSelected = InSelected;

}


FReply SDinoDomainInstanceActionButton::OnDuplicateClicked()
{
	if (OnDuplicatedDelegate.IsBound())
	{
		OnDuplicatedDelegate.Execute(ActionInstance.Get());
	}
	return FReply::Handled();
}

// ... (Existing OnClicked and OnDeleteClicked functions) ...

FReply SDinoDomainInstanceActionButton::OnClicked()
{
	bSelected = true;

	if (OnSelectedDelegate.IsBound()) { OnSelectedDelegate.Execute(ActionInstance.Get()); }
	return FReply::Handled();
}

FReply SDinoDomainInstanceActionButton::OnDeleteClicked()
{
	if (OnDeletedDelegate.IsBound()) { OnDeletedDelegate.Execute(ActionInstance.Get()); }
	return FReply::Handled();
}
