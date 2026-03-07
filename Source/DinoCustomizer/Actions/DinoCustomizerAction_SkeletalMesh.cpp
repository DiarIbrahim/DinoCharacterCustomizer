// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerAction_SkeletalMesh.h"

#include "Engine/SkinnedAssetCommon.h"

UDinoCustomizerAction_SkeletalMesh::UDinoCustomizerAction_SkeletalMesh()
{
	ActionDisplayName = FText::FromString("Set Skeletal mesh");
}

void UDinoCustomizerAction_SkeletalMesh::OnActionStarted_Implementation(
	const FDinoCustomizerActionActivationData& ActivationData)
{
	Super::OnActionStarted_Implementation(ActivationData);

	if(USkeletalMeshComponent* MeshComponent = Cast<USkeletalMeshComponent>(ActivationData.TargetDomainObject))
	{
		USkeletalMesh* MeshAsset = SkeletalMesh.LoadSynchronous();
		
		MeshComponent->SetSkeletalMesh(SkeletalMesh.LoadSynchronous());

		// clear existing materials
		MeshComponent->EmptyOverrideMaterials();

		// set new ones
		const int32 NumMaterials = MeshAsset->GetMaterials().Num();
		for (int32 i = 0; i < NumMaterials; ++i)
		{
			MeshComponent->SetMaterial(i, MeshAsset->GetMaterials()[i].MaterialInterface);
			
		}
		
		CommitAction();
	}
}
