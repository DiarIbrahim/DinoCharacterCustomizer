// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DomainContentSectionScreen.h"

#include "ClassViewerModule.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizerEditor/DinoButtons/DinoDomainInstanceActionButton.h"
#include "DinoCustomizerEditor/EditorClasses/DinoClassFilters.h"
#include "DinoCustomizerEditor/EditorClasses/SDinoAddButton.h"
#include "Kismet2/SClassPickerDialog.h"


void SDomainContentSectionScreen::Construct(const FArguments& InArgs)
{
	Database = InArgs._Database;
	SelectedDomain = InArgs._Domain;
	OnInstanceSelectedDelegate = InArgs._OnInstanceSelected;
	OnInstanceDeletedDelegate = InArgs._OnInstanceDeleted;


	FPropertyEditorModule& PropertyModule =
	FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bHideSelectionTip = true;
	DetailsViewArgs.bAllowSearch = false;
	DetailsViewArgs.bShowOptions = false;
	//DetailsViewArgs.

	// Create details view (this returns a TSharedRef)
	DetailsView = PropertyModule.CreateDetailView(DetailsViewArgs);
	

	ChildSlot
	[
		SNew(SBox)
		.Padding(4)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SNew(STextBlock)
				.Text_Lambda([this]()
				{
					return SelectedDomain.IsValid()
						? FText()
						: FText::FromString("Select a Domain To Edit");
				})
			]

			+ SOverlay::Slot()
			[
				SAssignNew(DomainContentVerticalBox, SVerticalBox)

			]
		]
	];

	RebuildDomainContentWindow();
}

void SDomainContentSectionScreen::SetDomain(UDinoCustomizerDatabaseDomain* InDomain)
{
	SelectedDomain = InDomain;
	RebuildDomainContentWindow();
}

void SDomainContentSectionScreen::SetDatabase(UDinoCustomizerDatabase* InDatabase)
{
	Database = InDatabase;
}

void SDomainContentSectionScreen::RebuildDomainContentWindow()
{
	if (!DomainContentVerticalBox.IsValid())
		return;

	DomainContentVerticalBox->ClearChildren();

	if (!SelectedDomain.IsValid())
		return;

	DetailsView->SetObject(SelectedDomain.Get());


	FSlateFontInfo TitleFont = FAppStyle::GetFontStyle("PropertyWindow.BoldFont");
	TitleFont.Size = 16;

	DomainContentVerticalBox->AddSlot()
	.AutoHeight()
	.HAlign(HAlign_Center)
	.Padding(0, 10)
	[
		SNew(STextBlock)
		.Text_Lambda([this]()
		{
			return SelectedDomain->GetDomainDisplayName();
		})
		.Font(TitleFont)
	];

	DomainContentVerticalBox->AddSlot()
	.AutoHeight()
	[
			DetailsView.ToSharedRef()
	];

	// ===== Add Instance Button =====

	DomainContentVerticalBox->AddSlot()
	.AutoHeight()
	.HAlign(HAlign_Left)
	.Padding(4, 9)
	[
		SNew(SDinoPlusButton)
		.LabelText(FText::FromString("Add Instance"))
		.ToolTipText(FText::FromString("Add New Instance to Domain"))
		.FixedSize(FVector2D(110, 24))
		.OnClicked(this, &SDomainContentSectionScreen::OnAddInstanceClicked)
	];

	

	TSharedPtr<SScrollBox> ScrollBox = nullptr;

	DomainContentVerticalBox->AddSlot()
	.FillHeight(1.0f)
	[
		SAssignNew(ScrollBox, SScrollBox)
	];

	InstanceButtons.Empty();
	
	for (UDinoCustomizerAction* Instance : SelectedDomain->Instances)
	{

		TSharedPtr<SDinoDomainInstanceActionButton> NewButton = nullptr;
		ScrollBox->AddSlot()
		.Padding(2)
		[
			SAssignNew(NewButton, SDinoDomainInstanceActionButton)
			.Action(Instance)
			.IsSelected(Instance == SelectedInstance)
			.OnDeleted(this, &SDomainContentSectionScreen::OnInstanceDeleted)
			.OnDuplicated(this, &SDomainContentSectionScreen::OnInstanceDuplicated)
			.OnSelected(this, &SDomainContentSectionScreen::HandleInstanceSelected)
		];

		InstanceButtons.Add(NewButton);
	}
	
}

void SDomainContentSectionScreen::OnInstanceDeleted(UDinoCustomizerAction* DinoCustomizerAction)
{
	SelectedDomain->RemoveInstance(DinoCustomizerAction);
	RebuildDomainContentWindow();
	OnInstanceDeletedDelegate.Execute(DinoCustomizerAction);

	if (DinoCustomizerAction == SelectedInstance)
	{
		SelectedInstance = nullptr;
	}
}

void SDomainContentSectionScreen::OnInstanceDuplicated(UDinoCustomizerAction* DinoCustomizerAction)
{
	SelectedDomain->DuplicateInstance(DinoCustomizerAction);
	RebuildDomainContentWindow();
}

FReply SDomainContentSectionScreen::OnAddInstanceClicked()
{
	if (!SelectedDomain.IsValid())
		return FReply::Handled();

	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;
	Options.bShowObjectRootClass = false;
	Options.bShowNoneOption = false;

	TSharedPtr<FDinoActionClassFilter> Filter = MakeShared<FDinoActionClassFilter>();
	Options.ClassFilters.Add(Filter.ToSharedRef());

	UClass* ChosenClass = nullptr;

	const FText TitleText = FText::FromString("Select Action Class");

	const bool bPressedOk =
		SClassPickerDialog::PickClass(
			TitleText,
			Options,
			ChosenClass,
			UDinoCustomizerAction::StaticClass()
		);

	if (bPressedOk && ChosenClass)
	{
		if(SelectedDomain->AddNewInstance(ChosenClass))
		{
			SelectedDomain->Modify();
			
			RebuildDomainContentWindow();
		}
		
	}

	return FReply::Handled();
}

void SDomainContentSectionScreen::HandleInstanceSelected(UDinoCustomizerAction* Instance)
{

	SelectedInstance = Instance;


	for(TSharedPtr<SDinoDomainInstanceActionButton> Btn :  InstanceButtons)
	{
		if(Btn->ActionInstance->GetUniqueID() != Instance->GetUniqueID())
		{
			Btn->SetSelected(false);
		}
	}
	
	
	if (OnInstanceSelectedDelegate.IsBound())
	{
		OnInstanceSelectedDelegate.Execute(Instance);
	}
}