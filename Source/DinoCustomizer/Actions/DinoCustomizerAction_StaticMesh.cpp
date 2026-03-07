// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerAction_StaticMesh.h"

UDinoCustomizerAction_StaticMesh::UDinoCustomizerAction_StaticMesh()
{
	ActionDisplayName = FText::FromString("Set Static mesh");

}

void UDinoCustomizerAction_StaticMesh::OnActionStarted_Implementation(
	const FDinoCustomizerActionActivationData& ActivationData)
{
	Super::OnActionStarted_Implementation(ActivationData);

	if(UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(ActivationData.TargetDomainObject))
	{
		UStaticMesh* MeshAsset = StaticMesh.LoadSynchronous();
		
		MeshComponent->SetStaticMesh(MeshAsset);

		// Clear any existing material overrides
		MeshComponent->EmptyOverrideMaterials();

		// apply new ones
		const int32 NumMaterials = StaticMesh->GetStaticMaterials().Num();
		for (int32 i = 0; i < NumMaterials; ++i)
		{
			UMaterialInterface* Mat = MeshAsset->GetMaterial(i);
			MeshComponent->SetMaterial(i, Mat);
		}

		
		CommitAction();

	}
}


