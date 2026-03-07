// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "ClassViewerFilter.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizer/Interfaces/DinoCustomizableActorInterface.h"

/**
 * 
 */
class  FDinoCustomizableInterfaceClassFilter : public IClassViewerFilter
{
public:

	/** The interface that must be implemented */
	const UClass* RequiredInterface = UDinoCustomizableActorInterface::StaticClass();

	virtual bool IsClassAllowed(
		const FClassViewerInitializationOptions& InInitOptions,
		const UClass* InClass,
		TSharedRef<FClassViewerFilterFuncs> InFilterFuncs
	) override
	{
		return InClass
			&& !InClass->HasAnyClassFlags(CLASS_Abstract)
			&& InClass->ImplementsInterface(RequiredInterface);
	}

	virtual bool IsUnloadedClassAllowed(
		const FClassViewerInitializationOptions& InInitOptions,
		const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData,
		TSharedRef<FClassViewerFilterFuncs> InFilterFuncs
	) override
	{
		return InUnloadedClassData->ImplementsInterface(RequiredInterface);
	}
};



class FDinoActionClassFilter : public IClassViewerFilter
{
public:

	virtual bool IsClassAllowed(
		const FClassViewerInitializationOptions& InInitOptions,
		const UClass* InClass,
		TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
	{
		return InClass->IsChildOf(UDinoCustomizerAction::StaticClass())
			&& !InClass->HasAnyClassFlags(CLASS_Abstract)
			&& !InClass->HasAnyClassFlags(CLASS_Deprecated)
			&& !InClass->HasAnyClassFlags(CLASS_NewerVersionExists);
	}

	virtual bool IsUnloadedClassAllowed(
		const FClassViewerInitializationOptions& InInitOptions,
		const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData,
		TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
	{
		return InUnloadedClassData->IsChildOf(UDinoCustomizerAction::StaticClass());
	}
};



class FDinoSubActionClassFilter : public IClassViewerFilter
{
public:

	virtual bool IsClassAllowed(
		const FClassViewerInitializationOptions& InInitOptions,
		const UClass* InClass,
		TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
	{
		return InClass->IsChildOf(UDinoCustomizerSubAction::StaticClass())
			&& !InClass->HasAnyClassFlags(CLASS_Abstract)
			&& !InClass->HasAnyClassFlags(CLASS_Deprecated)
			&& !InClass->HasAnyClassFlags(CLASS_NewerVersionExists);
	}

	virtual bool IsUnloadedClassAllowed(
		const FClassViewerInitializationOptions& InInitOptions,
		const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData,
		TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
	{
		return InUnloadedClassData->IsChildOf(UDinoCustomizerSubAction::StaticClass());
	}
};