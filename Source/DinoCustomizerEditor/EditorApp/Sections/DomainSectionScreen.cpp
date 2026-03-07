// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#include "DomainSectionScreen.h"

#include "DinoCustomizerEditor/DinoButtons/DinoDomainButton.h"
#include "DinoCustomizerEditor/DinoButtons/DinoListButton.h"
#include "DinoCustomizerEditor/EditorClasses/SDinoAddButton.h"
#include "DinoCustomizerEditor/Helpers/DinoCustomizerEditorHelper.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSeparator.h"

void SDomainSectionScreen::Construct(const FArguments& InArgs)
{
	Database = InArgs._Database;
	OnDomainSelectedDelegate = InArgs._OnDomainSelected;
	OnDomainDeletedDelegate = InArgs._OnDomainDeleted;

	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Left)
		.Padding(4, 9)
		[
			SNew(SDinoPlusButton)
			.FixedSize(FVector2D(110.0f, 24.0f))
			.ToolTipText(FText::FromString("Add New Customizable Domain"))
			.LabelText(FText::FromString("Add Domain"))
			.OnClicked(this, &SDomainSectionScreen::OnAddDomainClicked)
		]

		+ SVerticalBox::Slot()
		.MaxHeight(1)
		.Padding(0.0f, 10.0f)
		[
			SNew(SSeparator)
			.Thickness(.1f)
			.Visibility_Lambda([this]()
			{
				return (Database.IsValid() && !Database->Domains.IsEmpty())
					? EVisibility::Visible
					: EVisibility::Hidden;
			})
		]

		+ SVerticalBox::Slot()
		.FillHeight(999999)
		[
			SAssignNew(DomainsScrollBox, SScrollBox)
			.Visibility_Lambda([this]()
			{
				return (Database.IsValid() && !Database->Domains.IsEmpty())
					? EVisibility::Visible
					: EVisibility::Hidden;
			})
		]
	];

	RebuildDomainsUI();
}

void SDomainSectionScreen::RebuildDomainsUI()
{
	if (!DomainsScrollBox.IsValid() || !Database.IsValid())
		return;

	DomainsScrollBox->ClearChildren();
	DomainButtons.Empty();

	if (Database->Domains.IsEmpty())
		return;

	int32 Index = -1;
	for (UDinoCustomizerDatabaseDomain* Domain : Database->Domains)
	{
		Index++;
		
		TSharedPtr<SDinoDomainButton> Button;

		DomainsScrollBox->AddSlot()
		[
			SAssignNew(Button, SDinoDomainButton)
			.Domain(Domain)
			.Height(DomainButtonHeight)
			.DomainIndex(Index)
			.NumDomains(Database->Domains.Num())
			.IsSelected(
				SelectedDomain
				? SelectedDomain->GetDomainId() == Domain->GetDomainId()
				: false)
			.OnClicked(this, &SDomainSectionScreen::HandleDomainSelected)
			.OnDeleteClicked(this,&SDomainSectionScreen::HandleDomainDeleted)
			.OnMoveUpClicked(this, &SDomainSectionScreen::MoveDomainOrderUp)
			.OnMoveDownClicked(this, &SDomainSectionScreen::MoveDomainOrderDown)
		];

		DomainButtons.Add(Button);
	}

	DomainsScrollBox->AddSlot()
[
	SNew(SDinoListButton)
	.Height(90)
	.ItemIndex(1)
	.NumItems(3)
];

	DomainsScrollBox->AddSlot()
[
SNew(SDinoListButton)
.Height(65)
.ItemIndex(1)
.NumItems(3)
];
}

FReply SDomainSectionScreen::OnAddDomainClicked()
{
	if (!Database.IsValid())
		return FReply::Handled();

	// Let EditorApp handle creation if needed
	if (Database.IsValid())
	{
		if(Database->AddNewDatabaseDomain())
		{
			Database->Modify();
			RebuildDomainsUI();

		}
	}


	return FReply::Handled();
}

void SDomainSectionScreen::HandleDomainSelected(UDinoCustomizerDatabaseDomain* Domain)
{
	SelectedDomain = Domain;

	if (OnDomainSelectedDelegate.IsBound())
	{
		OnDomainSelectedDelegate.Execute(SelectedDomain);
	}

	for(auto Btn : DomainButtons)
	{
		if(Btn->GetDomain() == SelectedDomain)
		{
			Btn->SetSelected(true);
		}else
		{
			Btn->SetSelected(false);
		}
	}

}

void SDomainSectionScreen::HandleDomainDeleted(UDinoCustomizerDatabaseDomain* Domain)
{

	if(Database->RemoveDatabaseDomain(Domain))
	{
		
		if (SelectedDomain == Domain)
		{
			SelectedDomain = nullptr;
		}
		
		Database->Modify();
		RebuildDomainsUI();

		OnDomainDeletedDelegate.Execute(Domain);
	}
	
}

void SDomainSectionScreen::MoveDomainOrderUp(UDinoCustomizerDatabaseDomain* DinoCustomizerDatabaseDomain)
{
	if(Database->MoveDomainOrderUp(DinoCustomizerDatabaseDomain))
	{
		Database->Modify();
		RebuildDomainsUI();

		MoveMouseVertical(-DomainButtonHeight);

	}
}

void SDomainSectionScreen::MoveDomainOrderDown(UDinoCustomizerDatabaseDomain* DinoCustomizerDatabaseDomain)
{
	if(Database->MoveDomainOrderDown(DinoCustomizerDatabaseDomain))
	{
		Database->Modify();
		RebuildDomainsUI();

		MoveMouseVertical(DomainButtonHeight);
	}
}
