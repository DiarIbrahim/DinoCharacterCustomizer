// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCustomizerStudio.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "DinoCustomizer/Actions/DinoCustomizerAction.h"
#include "DinoCustomizer/Helpers/DinoCustomizerHelper.h"
#include "DinoCustomizer/Interfaces/DinoCustomizableActorInterface.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ADinoCustomizerStudio::ADinoCustomizerStudio()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CharacterPlacementLocation = CreateDefaultSubobject<USceneComponent>(TEXT("CharacterPlacementLocation"));
	CharacterPlacementLocation->SetupAttachment(Root);

	CharacterDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("CharacterDirection"));
	CharacterDirection->SetupAttachment(CharacterPlacementLocation);
	CharacterDirection->SetRelativeLocation(FVector(0, 0, 60));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Root);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SetRelativeRotation(FRotator(0, 180, 0));
	SpringArm->SetRelativeLocation(FVector(0, 0, 80));


	DefaultCameraSettings.DistanceToTarget = 260.0f;
	DefaultCameraSettings.LerpSpeed = 3;
	DefaultCameraSettings.RotationOffset = FRotator(0.f,-10.0f, 0.f);
	DefaultCameraSettings.TargetOffset = FVector(0.f, 0.f, 100.0f);
}

// Called when the game starts or when spawned
void ADinoCustomizerStudio::BeginPlay()
{

	CurrentCameraSettings.DistanceToTarget = SpringArm->TargetArmLength;
	CurrentCameraSettings.TargetOffset = SpringArm->GetComponentLocation();
	CurrentCameraSettings.RotationOffset = SpringArm->GetRelativeRotation() + FRotator(0.0f,180.0f,0.0f);

	Super::BeginPlay();
	
}



// Called every frame
void ADinoCustomizerStudio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if(IsValid(CurrentCustomizableActor) && CurrentCameraSettings.IsNearlyEqual(TargetCameraSettings) == false)
	{

			// Arm length
			CurrentCameraSettings.DistanceToTarget = FMath::FInterpTo(CurrentCameraSettings.DistanceToTarget, TargetCameraSettings.DistanceToTarget, DeltaTime, TargetCameraSettings.LerpSpeed);

			// FOV
			CurrentCameraSettings.FOV =  FMath::FInterpTo(CurrentCameraSettings.FOV, TargetCameraSettings.FOV, DeltaTime, TargetCameraSettings.LerpSpeed);

			// Rot
			CurrentCameraSettings.RotationOffset = FMath::RInterpTo(CurrentCameraSettings.RotationOffset, TargetCameraSettings.RotationOffset, DeltaTime, TargetCameraSettings.LerpSpeed);

			FVector TargetLocation = Root->GetComponentLocation() + TargetCameraSettings.TargetOffset;
			
			if(IsValid(CurrentCustomizableActorMainMesh) && CurrentCustomizableActorMainMesh->DoesSocketExist(TargetCameraSettings.CharacterSocketAsTarget))
			{
				// override to start from the socket location
				TargetLocation = CurrentCustomizableActorMainMesh->GetSocketLocation(TargetCameraSettings.CharacterSocketAsTarget) + TargetCameraSettings.TargetOffset;
			}

			// LOC
			CurrentCameraSettings.TargetOffset = FMath::VInterpTo(CurrentCameraSettings.TargetOffset, TargetLocation, DeltaTime, TargetCameraSettings.LerpSpeed);
			

			ApplyCurrentCameraSettings_Internal(CurrentCameraSettings);
			
		
	}
	
}

void ADinoCustomizerStudio::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

#if WITH_EDITOR

	FlushPersistentDebugLines(GetWorld());
	
	DrawDebugCircle(
		GetWorld(),
		CharacterPlacementLocation->GetComponentLocation(),
		20.0f,
		12,
		FColor::Green,
		true,
		-1,
		0,
		1,
		CharacterPlacementLocation->GetRightVector(),
		CharacterPlacementLocation->GetForwardVector(),
		false
		);


#endif
	
}

void ADinoCustomizerStudio::ApplyCustomizationAppearance(const FDinoCustomizationAppearance& AppearanceData)
{
	for(const auto& Pair : AppearanceData.GetDomainsAsMap())
	{
		const FGameplayTag Domain = Pair.Key;
		const FGameplayTag InstanceTag = Pair.Value;
		if(UDinoCustomizerAction* Action =  UDinoCustomizerHelper::GetCustomizationInstanceDataFromDatabase(CurrentCustomizationDataBase, Domain, InstanceTag))
		{
			ApplyCustomizationActionToDomain(Domain, Action);
		}
	}
}

void ADinoCustomizerStudio::ApplyCameraSettings(const FDinoCustomizerCameraSettings& InCameraSettings)
{
	if(TargetCameraSettings.IsNearlyEqual(InCameraSettings) ) return;

	TargetCameraSettings = InCameraSettings;
}

void ADinoCustomizerStudio::ApplyDefaultCameraSettings()
{
	TargetCameraSettings = DefaultCameraSettings;
}

bool ADinoCustomizerStudio::InitializeCustomizationFromDatabase(UDinoCustomizationDataBase* InCustomizationDatabase, bool bApplyMinimalAppearanceFromDataBase)
{

	if(IsValid(InCustomizationDatabase) == false ||  InCustomizationDatabase->CustomizableActorClass.IsNull() || InCustomizationDatabase->CustomizableDomains.IsEmpty()) return false;

	TSubclassOf<AActor> CustomizableActorClass = InCustomizationDatabase->CustomizableActorClass.LoadSynchronous();
	
	if(IsCustomizableClassAllowed(CustomizableActorClass) == false) return false;

	CurrentCustomizationDataBase = InCustomizationDatabase;

	FTransform SpawnTransform = CharacterPlacementLocation->GetComponentTransform();
	SpawnTransform.SetScale3D(FVector(1.0f));

	// Arrow Rotation 
	FRotator Rot = SpawnTransform.GetRotation().Rotator();
	Rot.Yaw = CharacterDirection->GetComponentRotation().Yaw;

	// apply DB Rotation offset
	FQuat RotWithDBOffset = SpawnTransform.GetRotation() * CurrentCustomizationDataBase->RotationOffsetInStudio.Quaternion();
	SpawnTransform.SetRotation(RotWithDBOffset);

	// apply DB location offset
	FVector LocDBOffset = SpawnTransform.GetLocation();
	LocDBOffset += CurrentCustomizationDataBase->StudioOffsetInStudio;
	SpawnTransform.SetLocation(LocDBOffset);
	

	// if a character, add half height to it
	if(ACharacter* AsCharacter = CustomizableActorClass->GetDefaultObject<ACharacter>())
	{
		FVector Loc = SpawnTransform.GetLocation();
		Loc.Z += AsCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		SpawnTransform.SetLocation(Loc);
	}



	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	CurrentCustomizableActor = GetWorld()->SpawnActor<ACharacter>(CustomizableActorClass,SpawnTransform,Params);
	
	CurrentCustomizableDomains = IDinoCustomizableActorInterface::Execute_GetCustomizableDomains(CurrentCustomizableActor);
	CurrentCustomizableActorMainMesh = IDinoCustomizableActorInterface::Execute_GetMainMesh(CurrentCustomizableActor);
	
	ApplyDefaultCameraSettings();


	if(bApplyMinimalAppearanceFromDataBase)
	{
		const FDinoCustomizationAppearance AppearanceData = UDinoCustomizerHelper::GenerateMinimalCustomizationAppearanceFromDatabase(CurrentCustomizationDataBase);
		
		ApplyCustomizationAppearance(AppearanceData);
	}

	return true;
}


bool ADinoCustomizerStudio::IsCustomizableClassAllowed(TSubclassOf<AActor> InActorClass) const
{
	if(IsValid(InActorClass) == false)return false;

	const AActor* DefaultCharacter = InActorClass->GetDefaultObject<AActor>();
	return DefaultCharacter->Implements<UDinoCustomizableActorInterface>();

}



void ADinoCustomizerStudio::ApplyCustomizationActionToDomain(const FGameplayTag& Domain, UDinoCustomizerAction* Action)
{
	if(CurrentCustomizableDomains.Contains(Domain) == false) return;
	
	UObject* DomainObject = CurrentCustomizableDomains[Domain];

	if(IsValid(Action))
	{

		FDinoCustomizerActionActivationData ActionData = FDinoCustomizerActionActivationData();
		ActionData.OwningCustomizerPawn = this;
		ActionData.TargetActor = CurrentCustomizableActor;
		ActionData.TargetDomainTag = Domain;
		ActionData.TargetDomainObject = DomainObject;
		
		Action->InitAction(ActionData);
	}
		
}

void ADinoCustomizerStudio::CommitCustomizationActionOnDomain(const FGameplayTag& DomainTag,
	const FGameplayTag& InstanceTag)
{
	CurrentCharacterAppearance.AddOrUpdateDomainData(DomainTag, InstanceTag);
}


void ADinoCustomizerStudio::ApplyCurrentCameraSettings_Internal(const FDinoCustomizerCameraSettings& CameraSettings)
{

	SpringArm->TargetArmLength = CameraSettings.DistanceToTarget;
	SpringArm->SetWorldLocation(CameraSettings.TargetOffset);
	SpringArm->SetRelativeRotation(FRotator(0.0f,180.0f,0.0f)+ CurrentCameraSettings.RotationOffset);
	Camera->FieldOfView = CameraSettings.FOV;
}