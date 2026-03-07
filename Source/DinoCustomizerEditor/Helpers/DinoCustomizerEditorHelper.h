// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

namespace DinoHelper
{
	FText TAG_TEXT(const FGameplayTag& InTag, bool bShowParent = false);


	static void MoveMouseVertical(float Amount)
	{
		FVector2D MousePos = FSlateApplication::Get().GetCursorPos();

		MousePos.Y += Amount;

		FSlateApplication::Get().SetCursorPos(MousePos);
	}

	static FIsPropertyVisible MakePropertyVisibilityDelegate()
	{
		return FIsPropertyVisible::CreateLambda([](const FPropertyAndParent& PropertyAndParent)
		{
			const FProperty& Prop = PropertyAndParent.Property;

			return Prop.HasAnyPropertyFlags(CPF_Edit) &&
				!Prop.HasAnyPropertyFlags(CPF_DisableEditOnInstance);
		});
	}
}
