// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Weapon.h"


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->InitBoxExtent(FVector(100, 100, 100 ));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::BeginOverlap);

	Weapon = CreateDefaultSubobject<AWeapon>(TEXT("Contained Item"));
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString name = OtherActor->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *name);
}

AWeapon* AItem::GrabItemContents()
{
	return Weapon;
}

