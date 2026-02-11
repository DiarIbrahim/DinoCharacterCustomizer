// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"


#define DECLARE_TAG(TagName) UE_DECLARE_GAMEPLAY_TAG_EXTERN(TagName)
#define DECLARE_TAG2(Category, TagName) UE_DECLARE_GAMEPLAY_TAG_EXTERN(Category##_##TagName)



namespace DinoCustomizationTags
{

	
	DECLARE_TAG2(CustomizableDomain, FullBody)
	DECLARE_TAG2(CustomizableDomain, UpperBody)
	DECLARE_TAG2(CustomizableDomain, LowerBody)
	DECLARE_TAG2(CustomizableDomain, Head)
	DECLARE_TAG2(CustomizableDomain, Hand)
	DECLARE_TAG2(CustomizableDomain, Foot)
	DECLARE_TAG2(CustomizableDomain, Hair)
	DECLARE_TAG2(CustomizableDomain, Beard)
	DECLARE_TAG2(CustomizableDomain, EyeGlasses)


	DECLARE_TAG2(CustomizableInstance, Instance_1)
	DECLARE_TAG2(CustomizableInstance, Instance_2)
	DECLARE_TAG2(CustomizableInstance, Instance_3)


	

	
}
