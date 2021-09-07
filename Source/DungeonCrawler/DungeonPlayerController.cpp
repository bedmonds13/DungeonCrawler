// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"



ADungeonPlayerController::ADungeonPlayerController()
{
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	this->bAutoManageActiveCameraTarget = true;
}

void ADungeonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ADungeonPlayerController::Forward);
	InputComponent->BindAxis("MoveBack", this, &ADungeonPlayerController::Back);
	InputComponent->BindAxis("MoveRight", this, &ADungeonPlayerController::Right);
	InputComponent->BindAxis("MoveLeft", this, &ADungeonPlayerController::Left);
	InputComponent->BindAction("Action",IE_Pressed,  this, &ADungeonPlayerController::Attack);
	InputComponent->BindAction("SpecialMove", IE_Pressed, this, &ADungeonPlayerController::CharacterSpecialMove);

}



void ADungeonPlayerController::Forward(float amount)
{
	ADungeonCharacter* character = Cast<ADungeonCharacter>(this->GetPawn());
	if (character != NULL)
	{
		character->Forward(amount);
	}
}

void ADungeonPlayerController::Back(float amount)
{
	ADungeonCharacter* character = Cast<ADungeonCharacter>(this->GetPawn());
	if (character != NULL)
	{
		character->Back(amount);
	}
}

void ADungeonPlayerController::Right(float amount)
{
	ADungeonCharacter* character = Cast<ADungeonCharacter>(this->GetPawn());
	if (character != NULL)
	{
		character->Right(amount);
	}
}

void ADungeonPlayerController::Left(float amount)
{
	ADungeonCharacter* character = Cast<ADungeonCharacter>(this->GetPawn());
	if (character != NULL)
	{
		character->Left(amount);
	}
}

void ADungeonPlayerController::Attack()
{
	ADungeonCharacter* character = Cast<ADungeonCharacter>(this->GetPawn());
	if (character != NULL)
	{
		FHitResult TraceHitResult;
		GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, TraceHitResult);
		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(character->GetActorLocation(), TraceHitResult.Location);

		character->Attack(rotation);
	}
	
}
void ADungeonPlayerController::CharacterSpecialMove()
{
	ADungeonCharacter* character = Cast<ADungeonCharacter>(this->GetPawn());
	if (character)
	{
		FHitResult TraceHitResult;
		GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, TraceHitResult);
		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(character->GetActorLocation(), TraceHitResult.Location);

		character->SpecialMove(rotation);
	}
}