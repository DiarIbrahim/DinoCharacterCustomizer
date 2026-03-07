// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"


struct DinoColors
{
	static FColor GetMainColor()
	{
		FLinearColor Color(1.0f, 0.245979f, 0.0f, 1.0f);
		return Color.ToFColor(true);
	}
};