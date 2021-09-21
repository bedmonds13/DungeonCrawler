// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"
#include "Materials/Material.h"
#include "UObject/ConstructorHelpers.h"
#include "Item.h"
#include "Kismet/KismetMathLibrary.h"
#include "ITakeHit.h"
#include "DungeonPlayerController.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"


// Sets default values
ADungeonCharacter::ADungeonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADungeonCharacter::BeginOverlap);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	inputDelayCount = 0;
	InputAllowed = true;
	//Character defaults
	MaxHealth = 10;
	hurtCount = 0;
	maxInputDelayCount = 1;
	


	

	
}

// Called when the game starts or when spawned
void ADungeonCharacter::BeginPlay()
{
	Super::BeginPlay();
	health = MaxHealth;
}

void ADungeonCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());
	AItem* newItem = Cast<AItem>(OtherActor);
	if (newItem != nullptr)
	{
		weapon = newItem->GrabItemContents();
	}
}



// Called every frame
void ADungeonCharacter::Tick(float DeltaTime)
{ 
	Super::Tick(DeltaTime);
	
	if (GetController() != NULL)
	{

		if (CursorToWorld != nullptr)
		{
			if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
			{
				if (UWorld* World = GetWorld())
				{
					FHitResult HitResult;
					FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
					FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
					FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
					Params.AddIgnoredActor(this);
					World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
					FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
					CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
				}
			}
			else if (APlayerController* PC = Cast<APlayerController>(GetController()))
			{
				FHitResult TraceHitResult;
				PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
				FVector CursorFV = TraceHitResult.ImpactNormal;
				FRotator CursorR = CursorFV.Rotation();
				CursorToWorld->SetWorldLocation(TraceHitResult.Location);
				CursorToWorld->SetWorldRotation(CursorR);
			}
		}
		if (InputAllowed == false)
		{
			if (inputDelayCount >= maxInputDelayCount)
			{
				InputAllowed = true;
				inputDelayCount =0;
			}
			else
			{
				inputDelayCount += DeltaTime;
			}
		}
	}
}


void ADungeonCharacter::Forward(float amount )
{
	if(InputAllowed)
		AddMovementInput(FVector(1, 0, 0), amount);
}

void ADungeonCharacter::Back(float amount)
{
	if (InputAllowed)
		AddMovementInput(FVector(-1, 0, 0), amount);
}

void ADungeonCharacter::Right(float amount)
{
	if (InputAllowed)
		AddMovementInput(FVector(0, 1, 0), amount);
}

void ADungeonCharacter::Left(float amount)
{
	if (InputAllowed)
		AddMovementInput(FVector(0, -1,0), amount);
}


void ADungeonCharacter::ResetInputTimer()
{
	InputAllowed = false;
	inputDelayCount = 0;
}


void ADungeonCharacter::TakeHit_Implementation(float damage, ADungeonCharacter* attackingCharacter, AttackType type)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit taken"));
	health -= damage;
	UGameplayStatics::PlaySoundAtLocation(Cast<UObject>(this),impactSound, GetActorLocation());
	if (health <= 0 && IsDead == false)
	{
		Die();
	}
	else
	{
		if(hurtSounds.Num() > 0)
		{
			if (hurtCount >= hurtSounds.Num())
			{
				hurtCount = 0;
			}
			UGameplayStatics::PlaySoundAtLocation(Cast<UObject>(this), (hurtSounds)[hurtCount], GetActorLocation());
			hurtCount++;
		}
	}
}

void ADungeonCharacter::SetInputAllowed(bool isInputAllowed)
{
	InputAllowed = isInputAllowed;
}

void ADungeonCharacter::SetCharacterHealth(float SavedHealth)
{
	this->health = SavedHealth;
}



void ADungeonCharacter::Attack_Implementation(FRotator newRotation)
{
	
/*
		FRotator rotationToMouse = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation() , mouseHit.Location);
	
		//Exclude pitch and roll to new actor rotation
*/
	ADungeonPlayerController* playerController = Cast<ADungeonPlayerController>(GetOwner());
	if (playerController)
	{
		if (InputAllowed) 
		{
			this->SetActorRotation(FRotator(0.0f, newRotation.Yaw, 0.0f));
			ResetInputTimer();
		}
	}
	
}

void ADungeonCharacter::Die_Implementation()
{

	if (deathAnimation)
		PlayAnimMontage(deathAnimation, 1, NAME_None);
	IsDead = true;

	AAIController* controller = Cast<AAIController>(GetController());
	if (controller)
	{
		UBlackboardComponent* blackboard = UAIBlueprintHelperLibrary::GetBlackboard(this);
		blackboard->SetValueAsBool("IsDead", IsDead);
	}


}


void ADungeonCharacter::SpecialMove_Implementation(FRotator newRotation)
{

	ADungeonPlayerController* playerController = Cast<ADungeonPlayerController>(GetOwner());
	if (playerController)
	{
		if (InputAllowed)
		{
			this->SetActorRotation(FRotator(0.0f, newRotation.Yaw, 0.0f));
			ResetInputTimer();
		}
	}

}



