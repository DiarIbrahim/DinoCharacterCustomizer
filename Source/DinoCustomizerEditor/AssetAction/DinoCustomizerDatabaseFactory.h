// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizerDatabaseFactory.generated.h"

/**
 * 
 */
UCLASS()
class  UDinoCustomizerDatabaseFactory : public UFactory
{
	GENERATED_BODY()

public:

	UDinoCustomizerDatabaseFactory(const FObjectInitializer& ObjectInitializer);

	virtual bool CanCreateNew() const override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
};
