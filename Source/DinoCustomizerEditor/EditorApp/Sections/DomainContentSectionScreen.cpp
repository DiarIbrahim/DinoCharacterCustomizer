// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DomainContentSectionScreen.h"

#include "ClassViewerModule.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizerEditor/DinoButtons/DinoDomainInstanceActionButton.h"
#include "DinoCustomizerEditor/EditorClasses/DinoClassFilters.h"
#include "DinoCustomizerEditor/EditorClasses/SDinoAddButton.h"
#include "DinoCustomizerEditor/Helpers/DinoCustomizerEditorHelper.h"
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
	SelectedInstance = nullptr;
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

	int32 Index = -1;
	for (UDinoCustomizerAction* Instance : SelectedDomain->Instances)
	{
		Index++;

		TSharedPtr<SDinoDomainInstanceActionButton> NewButton = nullptr;
		ScrollBox->AddSlot()
		[
			SAssignNew(NewButton, SDinoDomainInstanceActionButton)
			.Object(Instance)
			.IsSelected(Instance == SelectedInstance)
			.Height(InstanceButtonHeight)
			.ItemIndex(Index)
			.NumItems(SelectedDomain->Instances.Num())
			.Color_Lambda([this](){return SelectedDomain->DomainColor;})
			.OnClicked(this, &SDomainContentSectionScreen::HandleInstanceSelected)
			.OnDeleteClicked(this, &SDomainContentSectionScreen::OnInstanceDeleted)
			.OnDuplicateClicked(this, &SDomainContentSectionScreen::OnInstanceDuplicated)
			.OnMoveDownClicked(this, &SDomainContentSectionScreen::HandleInstanceMoveDown)
			.OnMoveUpClicked(this, &SDomainContentSectionScreen::HandleInstanceMoveUp)

		];

		InstanceButtons.Add(NewButton);
	}
	
}

void SDomainContentSectionScreen::OnInstanceDeleted(UObject* InInstanceObj)
{
	UDinoCustomizerAction* Instance = Cast<UDinoCustomizerAction>(InInstanceObj);
	
	if(SelectedDomain->RemoveInstance(Instance))
	{
		RebuildDomainContentWindow();
		OnInstanceDeletedDelegate.Execute(Instance);
		
		if (Instance == SelectedInstance)
		{
			SelectedInstance = nullptr;
		}
	}

}

void SDomainContentSectionScreen::OnInstanceDuplicated(UObject* InInstanceObj)
{
	UDinoCustomizerAction* Instance = Cast<UDinoCustomizerAction>(InInstanceObj);
	if(SelectedDomain->DuplicateInstance(Instance))
	{
		RebuildDomainContentWindow();
	}
	
}

void SDomainContentSectionScreen::HandleInstanceMoveDown(UObject* InInstanceObj)
{
	UDinoCustomizerAction* Instance = Cast<UDinoCustomizerAction>(InInstanceObj);
	if(SelectedDomain->MoveInstanceOrderDown(Instance))
	{
		RebuildDomainContentWindow();

		DinoHelper::MoveMouseVertical(InstanceButtonHeight);
	}
}

void SDomainContentSectionScreen::HandleInstanceMoveUp(UObject* InInstanceObj)
{
	UDinoCustomizerAction* Instance = Cast<UDinoCustomizerAction>(InInstanceObj);

	if(SelectedDomain->MoveInstanceOrderUp(Instance))
	{
		RebuildDomainContentWindow();
		DinoHelper::MoveMouseVertical(-InstanceButtonHeight);

	}
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

void SDomainContentSectionScreen::HandleInstanceSelected(UObject* InInstanceObj)
{

	SelectedInstance = Cast<UDinoCustomizerAction>(InInstanceObj);


	for(TSharedPtr<SDinoDomainInstanceActionButton> Btn :  InstanceButtons)
	{
		if(Btn->ActionInstance->GetUniqueID() == SelectedInstance->GetUniqueID())
		{
			Btn->SetSelected(true);
		}else
		{
			Btn->SetSelected(false);
			
		}
		
	}
	
	
	if (OnInstanceSelectedDelegate.IsBound())
	{
		OnInstanceSelectedDelegate.Execute(SelectedInstance.Get());
	}
}