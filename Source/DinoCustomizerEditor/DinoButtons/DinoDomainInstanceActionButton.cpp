#include "DinoDomainInstanceActionButton.h" // Ensure this matches your filename
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SImage.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizerEditor/Helpers/DinoCustomizerEditorHelper.h"




TSharedRef<SWidget> SDinoDomainInstanceActionButton::GetButtonContent()
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
									       ? FText::Format(FText::FromString("Instance Tag : {0}"), DinoHelper::TAG_TEXT(ActionInstance->InstanceTag))
									       : FText::GetEmpty();
							})
							.ColorAndOpacity(FLinearColor(0.3f, 0.7f, 1.0f))
						]
					];
	
}



void SDinoDomainInstanceActionButton::OnObjectSet(UObject* InObj)
{
	SDinoListButton::OnObjectSet(InObj);

	ActionInstance = Cast<UDinoCustomizerAction>(InObj);
}
