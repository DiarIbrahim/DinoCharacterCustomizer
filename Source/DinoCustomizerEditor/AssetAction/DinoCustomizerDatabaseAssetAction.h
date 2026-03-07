// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class FDinoCustomizerDatabaseAssetAction : public FAssetTypeActions_Base
{

	public:
	
	FDinoCustomizerDatabaseAssetAction(EAssetTypeCategories::Type InAssetCategory);

public: // FAssetTypeActions_Base interface

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, const EAssetTypeActivationOpenedMethod OpenedMethod, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;


private:
	EAssetTypeCategories::Type AssetCategory;

};
