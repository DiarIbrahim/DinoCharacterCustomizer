// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerAction_StaticMesh.h"

void UDinoCustomizerAction_StaticMesh::OnActionStarted_Implementation(
	const FDinoCustomizerActionActivationData& ActivationData)
{
	Super::OnActionStarted_Implementation(ActivationData);

	if(UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(ActivationData.TargetDomainObject))
	{
		MeshComponent->SetStaticMesh(StaticMesh);

		CommitAction();

	}
}

