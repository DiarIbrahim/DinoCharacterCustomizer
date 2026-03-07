#include "SubInstanceButton.h" // Ensure this matches your filename
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SImage.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizerEditor/Helpers/DinoCustomizerEditorHelper.h"



void SSubInstanceButton::OnObjectSet(UObject* InObj)
{
	SDinoListButton::OnObjectSet(InObj);

	SubInstance = Cast<UDinoCustomizerSubAction>(InObj);
}

TSharedRef<SWidget> SSubInstanceButton::GetButtonContent()
{
	FSlateFontInfo NameFont = FAppStyle::GetFontStyle("PropertyWindow.BoldFont");
	NameFont.Size = 13;

	return 				SNew(SHorizontalBox)

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
								return SubInstance.IsValid() && SubInstance->SubInstanceDisplayImage.IsValid()
									       ? EVisibility::Visible
									       : EVisibility::Hidden;
							})
							.Image_Lambda([this]() -> const FSlateBrush* {
								if (SubInstance.IsValid() && !SubInstance->SubInstanceDisplayImage.IsNull())
								{
									UTexture2D* CurrentTexture = SubInstance->SubInstanceDisplayImage.Get();
									if (!CurrentTexture)
									{
										CurrentTexture = SubInstance->SubInstanceDisplayImage.LoadSynchronous();
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
									       ? FText::Format(FText::FromString("Instance Tag : {0}"), DinoHelper::TAG_TEXT(SubInstance->SubInstanceTag))
									       : FText::GetEmpty();
							})
							.ColorAndOpacity(FLinearColor(0.3f, 0.7f, 1.0f))
						]
					];
	
}
