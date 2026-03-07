// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#include "SubInstanceSectionScreen.h"

#include "DinoCustomizerEditor/DinoButtons/SubInstanceButton.h"
#include "DinoCustomizerEditor/Helpers/DinoCustomizerEditorHelper.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSeparator.h"

void SSubInstanceSectionScreen::Construct(const FArguments& InArgs)
{
	CurrentSubInstance = InArgs._SubInstnce;
	Database = InArgs._Database;

	FPropertyEditorModule& PropertyModule =
		FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bHideSelectionTip = true;
	DetailsViewArgs.bAllowSearch = false;
	DetailsViewArgs.bShowOptions = false;

	// Create details view (this returns a TSharedRef)
	DetailsView = PropertyModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(CurrentSubInstance.Get());
	DetailsView->SetIsPropertyVisibleDelegate(DinoHelper::MakePropertyVisibilityDelegate());


	ChildSlot
	[

		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Select sub Instance To Modify"))
			.Visibility_Lambda([this]()
			{
				return CurrentSubInstance.IsValid() ? EVisibility::Hidden : EVisibility::Visible;
			})

		]

		+ SOverlay::Slot()
		[
			SNew(SVerticalBox)
			.Visibility_Lambda([this]()
			{
				return CurrentSubInstance.IsValid() ? EVisibility::Visible : EVisibility::Hidden;
			})
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				DetailsView.ToSharedRef()
			]

			
		]

	];

}

void SSubInstanceSectionScreen::SetSubInstance(UDinoCustomizerSubAction* InSubInstance)
{
	CurrentSubInstance = InSubInstance;
	DetailsView->SetObject(CurrentSubInstance.Get());
}
