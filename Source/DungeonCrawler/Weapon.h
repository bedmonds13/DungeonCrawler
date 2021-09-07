// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"



UENUM(BlueprintType)
enum  WeaponType {
	Blade UMETA(DisplayName = "Blade"),
	Axe UMETA(DisplayName = "Axe"),
	Bow UMETA(DisplayName = "Bow")
};



UCLASS()
class DUNGEONCRAWLER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<WeaponType> type;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};



