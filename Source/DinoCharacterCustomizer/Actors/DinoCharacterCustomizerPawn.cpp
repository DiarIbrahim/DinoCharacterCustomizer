// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCharacterCustomizerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "DinoCharacterCustomizer/Helpers/DinoCharacterCustomizerHelper.h"
#include "DinoCharacterCustomizer/Interfaces/DinoCustomizableCharacterInterface.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ADinoCharacterCustomizerPawn::ADinoCharacterCustomizerPawn()
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


}

// Called when the game starts or when spawned
void ADinoCharacterCustomizerPawn::BeginPlay()
{

	// init before begin play
	InitializeCharacter();

	CurrentCameraSettings.DistanceToTarget = SpringArm->TargetArmLength;
	CurrentCameraSettings.TargetOffset = SpringArm->GetComponentLocation();
	CurrentCameraSettings.RotationOffset = SpringArm->GetRelativeRotation() + FRotator(0.0f,180.0f,0.0f);
	
	ApplyDefaultCameraSettings();
	
	Super::BeginPlay();
	
}



// Called every frame
void ADinoCharacterCustomizerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if(CurrentCameraSettings.IsNearlyEqual(TargetCameraSettings) == false)
	{
		// Arm length
		CurrentCameraSettings.DistanceToTarget = FMath::FInterpTo(CurrentCameraSettings.DistanceToTarget, TargetCameraSettings.DistanceToTarget, DeltaTime, TargetCameraSettings.LerpSpeed);

		// FOV
		CurrentCameraSettings.FOV =  FMath::FInterpTo(CurrentCameraSettings.FOV, TargetCameraSettings.FOV, DeltaTime, TargetCameraSettings.LerpSpeed);

		// Rot
		CurrentCameraSettings.RotationOffset = FMath::RInterpTo(CurrentCameraSettings.RotationOffset, TargetCameraSettings.RotationOffset, DeltaTime, TargetCameraSettings.LerpSpeed);

		FVector TargetLocation = Root->GetComponentLocation() + TargetCameraSettings.TargetOffset;
		
		if(Character->GetMesh()->DoesSocketExist(TargetCameraSettings.CharacterSocketAsTarget))
		{
			// override to start from the socket location
			TargetLocation = Character->GetMesh()->GetSocketLocation(TargetCameraSettings.CharacterSocketAsTarget) + TargetCameraSettings.TargetOffset;
		}

		// LOC
		CurrentCameraSettings.TargetOffset = FMath::VInterpTo(CurrentCameraSettings.TargetOffset, TargetLocation, DeltaTime, TargetCameraSettings.LerpSpeed);
		

		ApplyCurrentCameraSettings_Internal(CurrentCameraSettings);
		
	}
}

void ADinoCharacterCustomizerPawn::OnConstruction(const FTransform& Transform)
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

void ADinoCharacterCustomizerPawn::ApplyCameraSettings(const FDinoCharacterCustomizerCameraSettings& InCameraSettings)
{
	if(TargetCameraSettings.IsNearlyEqual(InCameraSettings) ) return;

	TargetCameraSettings = InCameraSettings;
}

void ADinoCharacterCustomizerPawn::ApplyDefaultCameraSettings()
{
	TargetCameraSettings = DefaultCameraSettings;
}

void ADinoCharacterCustomizerPawn::InitializeCharacter()
{
	if(IsCharacterClassAllowed(CharacterClass) == false) return;

	FTransform SpawnTransform = CharacterPlacementLocation->GetComponentTransform();
	SpawnTransform.SetScale3D(FVector(1.0f));
	FRotator Rot = SpawnTransform.GetRotation().Rotator();
	Rot.Yaw = CharacterDirection->GetComponentRotation().Yaw;
	SpawnTransform.SetRotation(Rot.Quaternion());

	if(ACharacter* DefaultCharacter = CharacterClass->GetDefaultObject<ACharacter>())
	{
		FVector Loc = SpawnTransform.GetLocation();
		Loc.Z += DefaultCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		SpawnTransform.SetLocation(Loc);
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	Character = GetWorld()->SpawnActor<ACharacter>(CharacterClass,SpawnTransform,Params);
	
	CharacterCustomizableDomains = IDinoCustomizableCharacterInterface::Execute_GetCustomizableDomains(Character);
	
	
}

bool ADinoCharacterCustomizerPawn::IsCharacterClassAllowed(TSubclassOf<ACharacter> InCharacterClass) const
{
	if(IsValid(InCharacterClass) == false)return false;

	const ACharacter* DefaultCharacter = CharacterClass->GetDefaultObject<ACharacter>();
	return DefaultCharacter->Implements<UDinoCustomizableCharacterInterface>();

}

void ADinoCharacterCustomizerPawn::ApplyCharacterAppearance(const FDinoCharacterAppearance& CharacterAppearance)
{
	for(const auto& Pair : CharacterAppearance.GetDomainsAsMap())
	{
		const FGameplayTag Domain = Pair.Key;
		const FGameplayTag InstanceTag = Pair.Value;
		if(UDinoCharacterCustomizerAction* Action =  UDinoCharacterCustomizerHelper::GetCharacterInstanceDataFromDatabase(CharacterDataBase, Domain, InstanceTag))
		{
			ApplyCustomizationActionToDomain(Domain, Action);
		}
	}
}



void ADinoCharacterCustomizerPawn::ApplyCustomizationActionToDomain(const FGameplayTag& Domain, UDinoCharacterCustomizerAction* Action)
{
	if(CharacterCustomizableDomains.Contains(Domain) == false) return;
	
	UObject* DomainObject = CharacterCustomizableDomains[Domain];

	if(IsValid(Action))
	{

		FDinoCharacterCustomizerActionActivationData ActionData = FDinoCharacterCustomizerActionActivationData();
		ActionData.OwningCustomizerPawn = this;
		ActionData.TargetActor = Character;
		ActionData.TargetDomainTag = Domain;
		ActionData.TargetDomainObject = DomainObject;
		
		Action->InitAction(ActionData);
	}
		
}

void ADinoCharacterCustomizerPawn::CommitCustomizationActionOnDomain(const FGameplayTag& DomainTag,
	const FGameplayTag& InstanceTag)
{
	CurrentCharacterAppearance.AddOrUpdateDomainData(DomainTag, InstanceTag);
}


void ADinoCharacterCustomizerPawn::ApplyCurrentCameraSettings_Internal(const FDinoCharacterCustomizerCameraSettings& CameraSettings)
{

	SpringArm->TargetArmLength = CameraSettings.DistanceToTarget;
	SpringArm->SetWorldLocation(CameraSettings.TargetOffset);
	SpringArm->SetRelativeRotation(FRotator(0.0f,180.0f,0.0f)+ CurrentCameraSettings.RotationOffset);
	Camera->FieldOfView = CameraSettings.FOV;
}