#include "InstanceSubDomainButton.h" // Ensure this matches your filename
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SImage.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizerEditor/Helpers/DinoCustomizerEditorHelper.h"


TSharedRef<SWidget> SInstanceSubDomainButton::GetButtonContent()
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
								return InstanceSubDomain.IsValid() && InstanceSubDomain->SubDomainDisplayImage.IsValid()
									       ? EVisibility::Visible
									       : EVisibility::Hidden;
							})
							.Image_Lambda([this]() -> const FSlateBrush* {
								if (InstanceSubDomain.IsValid() && !InstanceSubDomain->SubDomainDisplayImage.IsNull())
								{
									UTexture2D* CurrentTexture = InstanceSubDomain->SubDomainDisplayImage.Get();
									if (!CurrentTexture)
									{
										CurrentTexture = InstanceSubDomain->SubDomainDisplayImage.LoadSynchronous();
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
									       ? FText::Format(FText::FromString("SubDomain Tag : {0}"), DinoHelper::TAG_TEXT(InstanceSubDomain->SubDomainTag))
									       : FText::GetEmpty();
							})
							.ColorAndOpacity(FLinearColor(0.3f, 0.7f, 1.0f))
						]
					];
	
}



void SInstanceSubDomainButton::OnObjectSet(UObject* InObj)
{
	SDinoListButton::OnObjectSet(InObj);

	InstanceSubDomain = Cast<UDinoCustomizerSubDomain>(InObj);
}
