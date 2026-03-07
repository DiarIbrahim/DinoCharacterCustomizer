// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerDatabaseEditorScreen.h"
#include "AssetThumbnail.h"
#include "../Sections/DomainSectionScreen.h"
#include "../Sections/DomainContentSectionScreen.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "SubDomainSectionScreen.h"
#include "SubInstanceSectionScreen.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "../Sections/InstanceSettingsScreen.h"


void SDinoCustomizerDatabaseEditorScreen::Construct(const FArguments& InArgs)
{
	Database = InArgs._Database;

	ChildSlot
	[
		SNew(SSplitter)
		.Orientation(Orient_Horizontal)

		+ SSplitter::Slot()
		.SizeRule(SSplitter::ESizeRule::FractionOfParent)
		.MinSize(200)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 4)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("DetailsView.CategoryTop"))
				.ToolTipText(FText::FromString(
					"Each Domain is a customizable Section That we can apply customization to, Anything that need to be customized can be a Domain"))
				.Padding(FMargin(8, 4))
				[
					SNew(STextBlock)
					.Text(FText::FromString("Customizable Domains"))
					.Font(FAppStyle::Get().GetFontStyle("PropertyWindow.BoldFont"))
					.ShadowOffset(FVector2D(1, 1))
				]
			]

			+ SVerticalBox::Slot()
			.FillHeight(1.0)
			[

				SAssignNew(DomainScreen, SDomainSectionScreen)
				.Database(Database)
				.OnDomainSelected(this, &SDinoCustomizerDatabaseEditorScreen::OnDomainsSelected)
				.OnDomainDeleted(this, &SDinoCustomizerDatabaseEditorScreen::OnDomainDeleted)
			]

		]

		+ SSplitter::Slot()
		.MinSize(200)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 4)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("DetailsView.CategoryTop"))
				.ToolTipText(FText::FromString(
					"Each Domain is a customization section of the customizable actor"))
				.Padding(FMargin(8, 4))
				[
					SNew(STextBlock)
					.Text(FText::FromString("Domain Content"))
					.Font(FAppStyle::Get().GetFontStyle("PropertyWindow.BoldFont"))
					.ShadowOffset(FVector2D(1, 1))
				]
			]

			+ SVerticalBox::Slot()
			.FillHeight(1.0)
			[
				SAssignNew(DomainContentScreen, SDomainContentSectionScreen)
				.Database(Database)
				.Domain(SelectedDomain)
				.OnInstanceSelected(this, &SDinoCustomizerDatabaseEditorScreen::OnDomainInstanceSelected)
				.OnInstanceDeleted(this,  &SDinoCustomizerDatabaseEditorScreen::OnDomainInstanceDeleted)
			]
		]

		+ SSplitter::Slot()
		.MinSize(200)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 4)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("DetailsView.CategoryTop"))
				.ToolTipText(FText::FromString(
					"Each instance is a change that can be applied to a domain"))
				.Padding(FMargin(8, 4))
				[
					SNew(STextBlock)
					.Text(FText::FromString("Instance Settings"))
					.Font(FAppStyle::Get().GetFontStyle("PropertyWindow.BoldFont"))
					.ShadowOffset(FVector2D(1, 1))
				]
			]

			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			[
				// DetailsView.ToSharedRef()
				SAssignNew(InstanceSettingsScreen, SInstanceSettingsScreen)
				.Database(Database)
				.Action(nullptr)
				.OnSubDomainSelected(this, &SDinoCustomizerDatabaseEditorScreen::OnSubDomainSelected)
				.OnSubDomainDeleted(this, &SDinoCustomizerDatabaseEditorScreen::OnSubDomainDeleted)
			]
		]
		+ SSplitter::Slot()
		.MinSize(200)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 0, 0, 4)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("DetailsView.CategoryTop"))
				.ToolTipText(FText::FromString(
					"Each instance can also have some sub instance changes, e.g. changing a color of a mesh"))
				.Padding(FMargin(8, 4))
				[
					SNew(STextBlock)
					.Text(FText::FromString("Sub Domain Settings"))
					.Font(FAppStyle::Get().GetFontStyle("PropertyWindow.BoldFont"))
					.ShadowOffset(FVector2D(1, 1))
				]
			]

			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			[
				SAssignNew(SubDomainSectionScreen, SSubDomainSectionScreen)
				.Database(Database)
				.SubDomain(SelectedSubDomain)
				.OnSubInstanceSelected(this, &SDinoCustomizerDatabaseEditorScreen::OnSubInstanceSelected)
				.OnSubInstanceDeleted(this, &SDinoCustomizerDatabaseEditorScreen::OnSubInstanceDeleted)
				
			]
		]
		+ SSplitter::Slot()
	.MinSize(200)
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0, 0, 0, 4)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("DetailsView.CategoryTop"))
			.ToolTipText(FText::FromString(
				"Each instance can also have some sub Domains or customization settings that apply to on instance only"))
			.Padding(FMargin(8, 4))
			[
				SNew(STextBlock)
				.Text(FText::FromString("Sub Instance Settings"))
				.Font(FAppStyle::Get().GetFontStyle("PropertyWindow.BoldFont"))
				.ShadowOffset(FVector2D(1, 1))
			]
		]

		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		[
			SAssignNew(SubInstanceSectionScreen, SSubInstanceSectionScreen)
			.Database(Database)
			.SubInstnce(SelectedSubInstance)
		]
	]
		
	];
}


void SDinoCustomizerDatabaseEditorScreen::OnDomainsSelected(UDinoCustomizerDatabaseDomain* Domain)
{
	if(Domain != SelectedDomain)
	{
		DomainContentScreen->SetDomain(Domain);
		InstanceSettingsScreen->SetInstance(nullptr);
		SubDomainSectionScreen->SetSubDomain(nullptr);
		SubInstanceSectionScreen->SetSubInstance(nullptr);
		SelectedDomain = Domain;
	}
}

void SDinoCustomizerDatabaseEditorScreen::OnDomainDeleted( UDinoCustomizerDatabaseDomain* DinoCustomizableDatabaseDomain)
{
	
	if(DinoCustomizableDatabaseDomain == SelectedDomain)
	{
		DomainContentScreen->SetDomain(nullptr);
		InstanceSettingsScreen->SetInstance(nullptr);
		SubDomainSectionScreen->SetSubDomain(nullptr);
		SubInstanceSectionScreen->SetSubInstance(nullptr);
	}
}

void SDinoCustomizerDatabaseEditorScreen::OnDomainInstanceSelected(UDinoCustomizerAction* DinoCustomizerAction)
{
	if(DinoCustomizerAction != SelectedInstance)
	{
		InstanceSettingsScreen->SetInstance(DinoCustomizerAction);
		SubDomainSectionScreen->SetSubDomain(nullptr);
		SubInstanceSectionScreen->SetSubInstance(nullptr);
		SelectedInstance = DinoCustomizerAction;
	}
}

void SDinoCustomizerDatabaseEditorScreen::OnDomainInstanceDeleted(UDinoCustomizerAction* DinoCustomizerAction)
{
	if(SelectedInstance == DinoCustomizerAction)
	{
		InstanceSettingsScreen->SetInstance(nullptr);
		SubDomainSectionScreen->SetSubDomain(nullptr);
		SubInstanceSectionScreen->SetSubInstance(nullptr);
	}
}

void SDinoCustomizerDatabaseEditorScreen::OnSubDomainSelected(UDinoCustomizerSubDomain* SubDomain)
{
	if(SubDomain != SelectedSubDomain)
	{
		SubDomainSectionScreen->SetSubDomain(SubDomain);
		SubInstanceSectionScreen->SetSubInstance(nullptr);
		SelectedSubDomain = SubDomain;
		
	}
}

void SDinoCustomizerDatabaseEditorScreen::OnSubDomainDeleted(UDinoCustomizerSubDomain* DinoCustomizerSubDomain)
{
	if(DinoCustomizerSubDomain == SelectedSubDomain)
	{
		SubDomainSectionScreen->SetSubDomain(nullptr);
		SubInstanceSectionScreen->SetSubInstance(nullptr);
	}
}

void SDinoCustomizerDatabaseEditorScreen::OnSubInstanceSelected(UDinoCustomizerSubAction* SubInstance)
{
	if(SubInstance != SelectedSubInstance){
		SubInstanceSectionScreen->SetSubInstance(SubInstance);
		SelectedSubInstance = SubInstance;
	
	}
}

void SDinoCustomizerDatabaseEditorScreen::OnSubInstanceDeleted(UDinoCustomizerSubAction* SubInstance)
{
	if(SelectedSubInstance == SubInstance)
	{
		SubInstanceSectionScreen->SetSubInstance(nullptr);
	}
}
