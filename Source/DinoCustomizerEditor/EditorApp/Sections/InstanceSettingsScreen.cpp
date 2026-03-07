// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#include "InstanceSettingsScreen.h"

#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizerEditor/DinoButtons/InstanceSubDomainButton.h"
#include "DinoCustomizerEditor/EditorClasses/SDinoAddButton.h"
#include "DinoCustomizerEditor/Helpers/DinoCustomizerEditorHelper.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSeparator.h"

void SInstanceSettingsScreen::Construct(const FArguments& InArgs)
{
	DomainColor = InArgs._DomainColor;
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
	DetailsView->SetIsPropertyVisibleDelegate(DinoHelper::MakePropertyVisibilityDelegate());

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

	int32 Index = -1;
	for (UDinoCustomizerSubDomain* SubDomain : CurrentInstance->SubDomains)
	{
		Index++;
		
		TSharedPtr<SInstanceSubDomainButton> Button;
		SubDomainScrollBox->AddSlot()
		[
			SAssignNew(Button, SInstanceSubDomainButton)
			.Object(SubDomain)
			.ItemIndex(Index)
			.Height(SubDomainButtonHeight)
			.Color_Lambda([this](){return DomainColor.Get();})
			.NumItems(CurrentInstance->SubDomains.Num())
			.IsSelected(SelectedSubDomain == SubDomain)
			.OnClicked(this, &SInstanceSettingsScreen::OnSubDomainSelected)
			.OnDuplicateClicked(this, &SInstanceSettingsScreen::OnSubDomainDuplicated)
			.OnDeleteClicked(this, &SInstanceSettingsScreen::OnSubDomainDeleted)
			.OnMoveDownClicked(this,  &SInstanceSettingsScreen::OnSubDomainMoveDown)
			.OnMoveUpClicked(this, &SInstanceSettingsScreen::OnSubDomainMoveUp)

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

void SInstanceSettingsScreen::OnSubDomainSelected(UObject* InSubDomainObj)
{

	SelectedSubDomain =  Cast<UDinoCustomizerSubDomain>(InSubDomainObj);
	
	OnInstanceSelectedDelegate.Execute(SelectedSubDomain.Get());
	
	for (TSharedPtr<SInstanceSubDomainButton> Button : SubDomainButtons)
	{

			Button->SetSelected(Button->InstanceSubDomain == SelectedSubDomain);
		
	}
}

void SInstanceSettingsScreen::OnSubDomainDuplicated(UObject* InSubDomainObj)
{
	UDinoCustomizerSubDomain* SubDomain = Cast<UDinoCustomizerSubDomain>(InSubDomainObj);

	if(CurrentInstance->DuplicateSubDomain(SubDomain))
	{
		Database->Modify();
		RebuildSubDomains();
	}

}

void SInstanceSettingsScreen::OnSubDomainDeleted(UObject* InSubDomainObj)
{
	UDinoCustomizerSubDomain* SubDomain = Cast<UDinoCustomizerSubDomain>(InSubDomainObj);
	
	if(CurrentInstance->RemoveSubDomain(SubDomain))
	{
		Database->Modify();
		RebuildSubDomains();

		OnInstanceDeletedDelegate.Execute(SubDomain);

		if(SelectedSubDomain == SubDomain)
		{
			SelectedSubDomain = nullptr;
		}
	}
}

void SInstanceSettingsScreen::OnSubDomainMoveDown(UObject* InSubDomainObj)
{
	UDinoCustomizerSubDomain* SubDomain = Cast<UDinoCustomizerSubDomain>(InSubDomainObj);
	if(CurrentInstance->MoveSubDomainOrderDown(SubDomain))
	{
		Database->Modify();
		RebuildSubDomains();

		DinoHelper::MoveMouseVertical(SubDomainButtonHeight);
	}
}

void SInstanceSettingsScreen::OnSubDomainMoveUp(UObject* InSubDomainObj)
{
	UDinoCustomizerSubDomain* SubDomain = Cast<UDinoCustomizerSubDomain>(InSubDomainObj);
	if(CurrentInstance->MoveSubDomainOrderUp(SubDomain))
	{
		Database->Modify();
		RebuildSubDomains();

		DinoHelper::MoveMouseVertical(-SubDomainButtonHeight);

	}
}
