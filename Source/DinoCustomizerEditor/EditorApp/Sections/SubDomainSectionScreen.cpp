// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#include "SubDomainSectionScreen.h"

#include "ClassViewerModule.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizerEditor/DinoButtons/InstanceSubDomainButton.h"
#include "DinoCustomizerEditor/DinoButtons/SubInstanceButton.h"
#include "DinoCustomizerEditor/EditorClasses/DinoClassFilters.h"
#include "DinoCustomizerEditor/EditorClasses/SDinoAddButton.h"
#include "DinoCustomizerEditor/Helpers/DinoCustomizerEditorHelper.h"
#include "Kismet2/SClassPickerDialog.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSeparator.h"

void SSubDomainSectionScreen::Construct(const FArguments& InArgs)
{
	CurrentSubDomain = InArgs._SubDomain;
	Database = InArgs._Database;
	DomainColor = InArgs._DomainColor;
	OnInstanceSelectedDelegate = InArgs._OnSubInstanceSelected;
	OnInstanceDeletedDelegate = InArgs._OnSubInstanceDeleted;

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
			.Text(FText::FromString("Select a Sub Domain Instance To Modify"))
			.Visibility_Lambda([this]()
			{
				return CurrentSubDomain.IsValid() ? EVisibility::Hidden : EVisibility::Visible;
			})

		]

		+ SOverlay::Slot()
		[
			SNew(SVerticalBox)
			.Visibility_Lambda([this]()
			{
				return CurrentSubDomain.IsValid() ? EVisibility::Visible : EVisibility::Hidden;
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
				.LabelText(FText::FromString("Add Sub Instance"))
				.ToolTipText(
					FText::FromString(
						"Add New Sub Instance, a customization that can be applied to this sub domain"))
				.FixedSize(FVector2D(130, 24))
				.OnClicked(this, &SSubDomainSectionScreen::OnAddSubInstanceClicked)

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

	RebuildSubInstances();
}

void SSubDomainSectionScreen::SetSubDomain(UDinoCustomizerSubDomain* InSubDomain)
{
	CurrentSubDomain = InSubDomain;

	DetailsView->SetObject(InSubDomain);

	RebuildSubInstances();
}

void SSubDomainSectionScreen::RebuildSubInstances()
{
	SubInstanceButtons.Empty();
	SubDomainScrollBox->ClearChildren();

	if (CurrentSubDomain.IsValid() == false) return;


	int32 Index = -1;
	
	for (UDinoCustomizerSubAction* SubInstance : CurrentSubDomain->SubInstances)
	{
		Index++;
		
		TSharedPtr<SSubInstanceButton> Button;
		SubDomainScrollBox->AddSlot()
		[
			SAssignNew(Button, SSubInstanceButton)
			.Object(SubInstance)
			.Height(SubInstanceButtonHeight)
			.Color_Lambda([this](){return DomainColor.Get();})
			.ItemIndex(Index)
			.NumItems(CurrentSubDomain->SubInstances.Num())
			.IsSelected(SelectedSubInstance == SubInstance)
			.OnClicked(this,   &SSubDomainSectionScreen::OnSubInstanceSelected)
			.OnDuplicateClicked(this, &SSubDomainSectionScreen::OnSubInstanceDuplicated)
			.OnDeleteClicked(this,    &SSubDomainSectionScreen::OnSubInstanceDeleted)
			.OnMoveDownClicked(this, &SSubDomainSectionScreen::OnSubInstanceMoveDown)
			.OnMoveUpClicked(this, &SSubDomainSectionScreen::OnSubInstanceMoveUp)

		];

		SubInstanceButtons.Add(Button);
	}
		
}

FReply SSubDomainSectionScreen::OnAddSubInstanceClicked()
{

	
	if (IsValid(CurrentSubDomain.Get()))
	{

		FClassViewerInitializationOptions Options;
		Options.Mode = EClassViewerMode::ClassPicker;
		Options.bShowObjectRootClass = false;
		Options.bShowNoneOption = false;

		TSharedPtr<FDinoSubActionClassFilter> Filter = MakeShared<FDinoSubActionClassFilter>();
		Options.ClassFilters.Add(Filter.ToSharedRef());

		UClass* ChosenClass = nullptr;

		const FText TitleText = FText::FromString("Select Sub Action Class");

		const bool bPressedOk =
			SClassPickerDialog::PickClass(
				TitleText,
				Options,
				ChosenClass,
				UDinoCustomizerAction::StaticClass()
			);

		if (bPressedOk && ChosenClass)
		{
			if (UDinoCustomizerSubAction* SubDomain = CurrentSubDomain->AddSubInstances(ChosenClass))
			{
				Database->Modify();
				RebuildSubInstances();
			}
		
		}

	}

	return FReply::Unhandled();
}

void SSubDomainSectionScreen::OnSubInstanceMoveUp(UObject* InSubInstanceObj)
{
	UDinoCustomizerSubAction* SubInstance = Cast<UDinoCustomizerSubAction>(InSubInstanceObj);

	if(CurrentSubDomain->MoveSubInstanceOrderUp(SubInstance))
	{
		Database->Modify();
		RebuildSubInstances();
		DinoHelper::MoveMouseVertical(-SubInstanceButtonHeight);
	}

}

void SSubDomainSectionScreen::OnSubInstanceMoveDown(UObject* InSubInstanceObj)
{
	UDinoCustomizerSubAction* SubInstance = Cast<UDinoCustomizerSubAction>(InSubInstanceObj);

	if(CurrentSubDomain->MoveSubInstanceOrderDown(SubInstance))
	{
		Database->Modify();
		RebuildSubInstances();

		DinoHelper::MoveMouseVertical(SubInstanceButtonHeight);

	}

}

void SSubDomainSectionScreen::OnSubInstanceSelected(UObject* InSubInstanceObj)
{

	SelectedSubInstance = Cast<UDinoCustomizerSubAction>(InSubInstanceObj);
	
	OnInstanceSelectedDelegate.Execute(SelectedSubInstance.Get());
	
	for (TSharedPtr<SSubInstanceButton> Button : SubInstanceButtons)
	{
			Button->SetSelected(Button->SubInstance == SelectedSubInstance);
	}
}

void SSubDomainSectionScreen::OnSubInstanceDuplicated(UObject* InSubInstanceObj)
{
	UDinoCustomizerSubAction* SubInstance = Cast<UDinoCustomizerSubAction>(InSubInstanceObj);

	if(CurrentSubDomain->DuplicateSubInstances(SubInstance))
	{
		Database->Modify();
		RebuildSubInstances();
	}

}

void SSubDomainSectionScreen::OnSubInstanceDeleted(UObject* InSubInstanceObj)
{
	UDinoCustomizerSubAction* SubInstance = Cast<UDinoCustomizerSubAction>(InSubInstanceObj);

	if(CurrentSubDomain->RemoveSubInstances(SubInstance))
	{
		Database->Modify();
		RebuildSubInstances();
		OnInstanceDeletedDelegate.Execute(SubInstance);

		if(SelectedSubInstance == SubInstance)
		{
			SelectedSubInstance = nullptr;
		}
	}
}
