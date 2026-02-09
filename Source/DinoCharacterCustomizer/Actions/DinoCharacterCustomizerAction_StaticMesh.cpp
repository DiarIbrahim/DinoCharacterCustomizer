// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCharacterCustomizerAction_StaticMesh.h"

void UDinoCharacterCustomizerAction_StaticMesh::OnActionStarted_Implementation(
	const FDinoCharacterCustomizerActionActivationData& ActivationData)
{
	Super::OnActionStarted_Implementation(ActivationData);

	if(UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(ActivationData.TargetDomainObject))
	{
		MeshComponent->SetStaticMesh(StaticMesh);

		CommitAction();

	}
}

