// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#include "InstanceSettingsScreen.h"

#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizerEditor/DinoButtons/InstanceSubDomainButton.h"
#include "DinoCustomizerEditor/EditorClasses/SDinoAddButton.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSeparator.h"

void SInstanceSettingsScreen::Construct(const FArguments& InArgs)
{
	CurrentInstance = InArgs._Action;
	Database = InArgs._Database;
	OnInstanceSelectedDelegate = InArgs._OnSubDomainSelected;
	OnInstanceDeletedDelegate = InArgs._OnSubDomainDeleted;

	FPropertyEditorModule& PropertyModule =
		FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bHideSelectionTip = true;
	DetailsViewArgs.bAllowSearch = false;
	DetailsViewArgs.bShowOptions = false;

	// Create details view (this returns a TSharedRef)
	DetailsView = PropertyModule.CreateDetailView(DetailsViewArgs);

	ChildSlot
	[

		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Select an Instance To Modify"))
			.Visibility_Lambda([this]()
			{
				return CurrentInstance.IsValid() ? EVisibility::Hidden : EVisibility::Visible;
			})

		]

		+ SOverlay::Slot()
		[
			SNew(SVerticalBox)
			.Visibility_Lambda([this]()
			{
				return CurrentInstance.IsValid() ? EVisibility::Visible : EVisibility::Hidden;
			})
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				DetailsView.ToSharedRef()
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SSpacer)
				.Size(FVector2D(0, 15))
			]
			

			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Left)
			.Padding(5,0)
			[
				SNew(SDinoPlusButton)
				.LabelText(FText::FromString("Add Sub Domain"))
				.ToolTipText(
					FText::FromString(
						"Add New Sub Domain, an other customization level that only applies to this instance"))
				.FixedSize(FVector2D(130, 24))
				.OnClicked(this, &SInstanceSettingsScreen::OnAddSubDomainClicked)

			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SSpacer)
				.Size(FVector2D(0, 10))
			]
			
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Top)
			.Padding(5,0)
			.FillHeight(1.0f)
			[
				SAssignNew(SubDomainScrollBox, SScrollBox)
			]


		]

	];

	RebuildSubDomains();
}

void SInstanceSettingsScreen::SetInstance(UDinoCustomizerAction* InActionInstance)
{
	CurrentInstance = InActionInstance;

	DetailsView->SetObject(InActionInstance);

	RebuildSubDomains();
}

void SInstanceSettingsScreen::RebuildSubDomains()
{
	SubDomainButtons.Empty();
	SubDomainScrollBox->ClearChildren();

	if (CurrentInstance.IsValid() == false) return;

	for (UDinoCustomizerSubDomain* SubDomain : CurrentInstance->SubDomains)
	{
		TSharedPtr<SInstanceSubDomainButton> Button;
		SubDomainScrollBox->AddSlot()
		[
			SAssignNew(Button, SInstanceSubDomainButton)
			.SubDomain(SubDomain)
			.IsSelected(SelectedSubDomain == SubDomain)
			.OnSelected(this, &SInstanceSettingsScreen::OnSubDomainSelected)
			.OnDuplicated(this, &SInstanceSettingsScreen::OnSubDomainDuplicated)
			.OnDeleted(this, &SInstanceSettingsScreen::OnSubDomainDeleted)
		];

		SubDomainButtons.Add(Button);
	}
}

FReply SInstanceSettingsScreen::OnAddSubDomainClicked()
{
	if (IsValid(CurrentInstance.Get()))
	{
		if (UDinoCustomizerSubDomain* SubDomain = CurrentInstance->AddSubDomain())
		{
			Database->Modify();
			RebuildSubDomains();
			// broadcast the change
		}
	}

	return FReply::Unhandled();
}

void SInstanceSettingsScreen::OnSubDomainSelected(UDinoCustomizerSubDomain* DinoCustomizerSubDomain)
{

	OnInstanceSelectedDelegate.Execute(DinoCustomizerSubDomain);
	SelectedSubDomain = DinoCustomizerSubDomain;
	
	for (TSharedPtr<SInstanceSubDomainButton> Button : SubDomainButtons)
	{
		if (Button->InstanceSubDomain != DinoCustomizerSubDomain)
		{
			Button->SetIsSelected(false);
		}
	}
}

void SInstanceSettingsScreen::OnSubDomainDuplicated(UDinoCustomizerSubDomain* DinoCustomizerSubDomain)
{
	if(CurrentInstance->DuplicateSubDomain(DinoCustomizerSubDomain))
	{
		Database->Modify();
		RebuildSubDomains();
	}

}

void SInstanceSettingsScreen::OnSubDomainDeleted(UDinoCustomizerSubDomain* DinoCustomizerSubDomain)
{
	if(CurrentInstance->RemoveSubDomain(DinoCustomizerSubDomain))
	{
		Database->Modify();
		RebuildSubDomains();

		OnInstanceDeletedDelegate.Execute(DinoCustomizerSubDomain);

		if(SelectedSubDomain == DinoCustomizerSubDomain)
		{
			SelectedSubDomain = nullptr;
		}
	}
}
