// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerSubAction_ApplyMaterial.h"

UDinoCustomizerSubAction_ApplyMaterial::UDinoCustomizerSubAction_ApplyMaterial()
{
	SubInstanceDisplayName = FText::FromString("Apply Material");
}

void UDinoCustomizerSubAction_ApplyMaterial::OnActionStarted_Implementation(UDinoCustomizerAction* OwnerAction,
                                                                            UObject* TargetObject)
{
	Super::OnActionStarted_Implementation(OwnerAction, TargetObject);

	if(Material.IsNull()) return;

	if(UMeshComponent* Mesh = Cast<UMeshComponent>(TargetObject) )
	{
		Mesh->CleanUpOverrideMaterials();
		
		Mesh->SetMaterial(0, Material.LoadSynchronous());
	}
}
