// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"



FText TAG_TEXT(const FGameplayTag& InTag, bool bShowParent = false);


static void MoveMouseVertical(float Amount)
{
	FVector2D MousePos = FSlateApplication::Get().GetCursorPos();

	MousePos.Y += Amount;

	FSlateApplication::Get().SetCursorPos(MousePos);
}
