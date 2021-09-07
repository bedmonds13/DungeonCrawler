// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DungeonCharacter.h"
#include "DungeonPlayerController.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ADungeonPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADungeonPlayerController();
	virtual void SetupInputComponent() override;

	

	ADungeonCharacter* playerCharacter;
	void Forward(float amount);
	void Back(float amount);
	void Right(float amount);
	void Left(float amount);
	void Attack();
	void CharacterSpecialMove();
private:

		
	

};
