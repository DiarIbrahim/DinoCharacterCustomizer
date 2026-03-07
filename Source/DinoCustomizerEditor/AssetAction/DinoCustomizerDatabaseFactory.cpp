// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerDatabaseFactory.h"

#include "DinoCustomizer/Data/DinoCustomizerDatabase.h"

UDinoCustomizerDatabaseFactory::UDinoCustomizerDatabaseFactory(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	SupportedClass = UDinoCustomizerDatabase::StaticClass();
}

bool UDinoCustomizerDatabaseFactory::CanCreateNew() const
{
	return true;
}

UObject* UDinoCustomizerDatabaseFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName,
                                                          EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UDinoCustomizerDatabase* NewDatabase = NewObject<UDinoCustomizerDatabase>(InParent, InName, Flags);
	return NewDatabase;
}
