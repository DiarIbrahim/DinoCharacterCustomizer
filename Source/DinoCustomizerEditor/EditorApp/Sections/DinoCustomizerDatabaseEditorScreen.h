// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizer/Actions/SubDomain/DinoCustomizerSubDomain.h"
#include "Widgets/SCompoundWidget.h"
#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"

class SDinoDomainButton;

class  SDinoCustomizerDatabaseEditorScreen : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SDinoCustomizerDatabaseEditorScreen) {}
	SLATE_ARGUMENT(TWeakObjectPtr<UDinoCustomizerDatabase>, Database)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);


private:


	// Data base we are editing 
	TWeakObjectPtr<UDinoCustomizerDatabase> Database;

	// currently Selected and we are Editing
	TWeakObjectPtr<UDinoCustomizerDatabaseDomain>   SelectedDomain    = nullptr;
	TWeakObjectPtr<UDinoCustomizerAction>           SelectedInstance  = nullptr;
	TWeakObjectPtr<UDinoCustomizerSubDomain>        SelectedSubDomain = nullptr;
	TWeakObjectPtr<UDinoCustomizerSubAction>        SelectedSubInstance = nullptr;
	

	// Editor screens
	 TSharedPtr<class SDomainSectionScreen>        DomainScreen;
	 TSharedPtr<class SDomainContentSectionScreen> DomainContentScreen;
	 TSharedPtr<class SInstanceSettingsScreen>     InstanceSettingsScreen;
	 TSharedPtr<class SSubDomainSectionScreen>     SubDomainSectionScreen;
	 TSharedPtr<class SSubInstanceSectionScreen>   SubInstanceSectionScreen;

	
	void OnDomainsSelected(UDinoCustomizerDatabaseDomain* Domain);
	void OnDomainDeleted(UDinoCustomizerDatabaseDomain* DinoCustomizableDatabaseDomain);

	void OnDomainInstanceSelected(UDinoCustomizerAction* Instance) ;
	void OnDomainInstanceDeleted(UDinoCustomizerAction* DinoCustomizerAction);

	void OnSubDomainSelected(UDinoCustomizerSubDomain* SubDomain) ;
	void OnSubDomainDeleted(UDinoCustomizerSubDomain* DinoCustomizerSubDomain);

	void OnSubInstanceSelected(UDinoCustomizerSubAction* SubInstance) ;
	void OnSubInstanceDeleted(UDinoCustomizerSubAction* SubInstance) ;



};
