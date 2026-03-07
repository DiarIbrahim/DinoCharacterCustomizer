// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerEditorHelper.h"




FText TAG_TEXT(const FGameplayTag& InTag, bool bShowParent)
{
	FText Text;
	if(!bShowParent)
	{
		FString TagString = InTag.ToString();
		FString R,L;
		TagString.Split(".", &L, &R, ESearchCase::IgnoreCase,ESearchDir::FromStart);

		Text = FText::FromString(R);
		
	}else
	{
		Text = FText::FromString(InTag.ToString());
	}
	
	return Text;
}
