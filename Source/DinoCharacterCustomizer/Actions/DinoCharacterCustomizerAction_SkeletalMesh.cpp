// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCharacterCustomizerAction_SkeletalMesh.h"

void UDinoCharacterCustomizerAction_SkeletalMesh::OnActionStarted_Implementation(
	const FDinoCharacterCustomizerActionActivationData& ActivationData)
{
	Super::OnActionStarted_Implementation(ActivationData);

	if(USkeletalMeshComponent* MeshComponent = Cast<USkeletalMeshComponent>(ActivationData.TargetDomainObject))
	{
		MeshComponent->SetSkeletalMesh(SkeletalMesh);

		CommitAction();
	}
}
