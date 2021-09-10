// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSpecialNotify.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "DungeonCharacter.h"

void UCharacterSpecialNotify::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Orange, __FUNCTION__);

	auto character = Cast<ADungeonCharacter>(MeshComp->GetOwner());
	if (character)
	{
		character->SpecialImpactEvent();
	}

}