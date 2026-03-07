// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"
#include "Widgets/SCompoundWidget.h"

class UDinoCustomizerDatabase;



class SSubInstanceSectionScreen : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SSubInstanceSectionScreen) {}
	SLATE_ARGUMENT(TWeakObjectPtr<UDinoCustomizerDatabase>, Database)
	SLATE_ARGUMENT(TWeakObjectPtr<UDinoCustomizerSubAction>, SubInstnce)
		
SLATE_END_ARGS()

void Construct(const FArguments& InArgs);

	void SetSubInstance(UDinoCustomizerSubAction* InSubInstance);


private:


	
	// Incoming
	TWeakObjectPtr<UDinoCustomizerDatabase> Database;
	TWeakObjectPtr<UDinoCustomizerSubAction> CurrentSubInstance;


	// Details 
	mutable TSharedPtr<IDetailsView> DetailsView;

};