// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class SDinoPlusButton : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDinoPlusButton)
	: _LabelText(FText::FromString("Add")) // Default text
			, _FixedSize(FVector2D(64.0f, 24.0f))  // Native compact size
		{}
	SLATE_ATTRIBUTE(FText, LabelText)
	SLATE_ARGUMENT(FVector2D, FixedSize)
	SLATE_EVENT(FOnClicked, OnClicked)
SLATE_END_ARGS()

void Construct(const FArguments& InArgs)
	{
		ChildSlot
		[
			// 1. SBox strictly enforces the fixed size so it never stretches
			SNew(SBox)
			.WidthOverride(InArgs._FixedSize.X)
			.HeightOverride(InArgs._FixedSize.Y)
			[
				// 2. Standard "Button" style gives the exact dark-gray background from your image
				SNew(SButton)
				.ButtonStyle(FAppStyle::Get(), "Button")
				.ContentPadding(FMargin(4.0f, 0.0f))
				.OnClicked(InArgs._OnClicked)
				[
					SNew(SHorizontalBox)
                    
					// The Green Plus Icon
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(2, 0, 4, 0)
					[
						SNew(SImage)
						.Image(FAppStyle::GetBrush("Icons.Plus"))
						.DesiredSizeOverride(FVector2D(14, 14))
						.ColorAndOpacity(FLinearColor(0.4f, 0.85f, 0.4f, 1.0f)) // Matches UE Add Green
					]

					// The Text Label
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text(InArgs._LabelText)
						.Font(FAppStyle::GetFontStyle("PropertyWindow.NormalFont"))
					]
				]
			]
		];
	}
};