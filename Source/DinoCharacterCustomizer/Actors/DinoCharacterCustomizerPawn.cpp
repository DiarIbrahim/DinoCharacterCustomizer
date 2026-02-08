// Code By : Diar Ibrahim,  Contact :  https://www.linkedin.com/in/diar-ibrahim-ali/


#include "DinoCharacterCustomizerPawn.h"

#include "PrimitiveSceneDesc.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "DinoCharacterCustomizer/Helpers/DinoCharacterCustomizerHelper.h"
#include "DinoCharacterCustomizer/Interfaces/DinoCustomizableCharacterInterface.h"
#include "GameFramework/Character.h"


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

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(Root);



}

// Called when the game starts or when spawned
void ADinoCharacterCustomizerPawn::BeginPlay()
{

	// init before begin play
	InitializeCharacter();

	
	Super::BeginPlay();
	
}

// Called every frame
void ADinoCharacterCustomizerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
		ModifyCustomizableDomainMesh(Pair.Key, Pair.Value);
	}
}

void ADinoCharacterCustomizerPawn::ModifyCustomizableDomainMesh(FGameplayTag Domain, FGameplayTag InstanceTag)
{
	if(CharacterCustomizableDomains.Contains(Domain) == false) return;

	
	if(USkeletalMeshComponent* MeshComponent = *CharacterCustomizableDomains.Find(Domain))
	{
		FDinoCustomizableInstanceData OutInstanceData;
		if(UDinoCharacterCustomizerHelper::GetCharacterInstanceData(CharacterDataBase, Domain, InstanceTag,OutInstanceData ))
		{
			
			MeshComponent->SetSkeletalMesh(OutInstanceData.InstanceMesh.LoadSynchronous());

			// update appearance data
			CurrentCharacterAppearance.AddOrUpdateDomainData(Domain, InstanceTag);
			
			// play animations here
			// broad cast the change
			// save an instance of current changes
			
		}
		
	}
}


