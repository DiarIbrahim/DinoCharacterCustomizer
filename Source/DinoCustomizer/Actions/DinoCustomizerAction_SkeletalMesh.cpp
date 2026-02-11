// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerAction_SkeletalMesh.h"

void UDinoCustomizerAction_SkeletalMesh::OnActionStarted_Implementation(
	const FDinoCustomizerActionActivationData& ActivationData)
{
	Super::OnActionStarted_Implementation(ActivationData);

	if(USkeletalMeshComponent* MeshComponent = Cast<USkeletalMeshComponent>(ActivationData.TargetDomainObject))
	{
		MeshComponent->SetSkeletalMesh(SkeletalMesh.LoadSynchronous());

		CommitAction();
	}
}
