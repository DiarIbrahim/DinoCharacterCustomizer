// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/

#pragma once

#include "CoreMinimal.h"
#include "DinoCustomizerCameraSettings.generated.h"

USTRUCT(BlueprintType)
struct FDinoCustomizerCameraSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceToTarget = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CharacterSocketAsTarget = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TargetOffset = FVector(0.0f,0.0f,80);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator RotationOffset = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LerpSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 5, UIMin = 5, ClampMax= 170,UIMax=170))
	float FOV  = 90.0f;

	
	bool IsNearlyEqual(const FDinoCustomizerCameraSettings& Other, float Tolerance = .1f) const
	{
		if(FMath::IsNearlyEqual(Other.DistanceToTarget, DistanceToTarget, Tolerance) == false)
		{
			return false;
		}

		if(TargetOffset.Equals(Other.TargetOffset, Tolerance) == false)
		{
			return false;
		}
		
		if (RotationOffset.Equals(Other.RotationOffset, Tolerance) == false)
		{
			return false;
		}

		if (FMath::IsNearlyEqual(Other.FOV, FOV, Tolerance) == false)
		{
			return false;
		}
		
		return true;
	}
	
};