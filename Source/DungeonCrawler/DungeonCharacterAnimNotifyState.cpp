// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonCharacterAnimNotifyState.h"

void UDungeonCharacterAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	MeshComp->bPauseAnims = true;
	UE_LOG(LogTemp, Warning, TEXT("Player should be destroyed"));
}

void UDungeonCharacterAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float duration)
{
	MeshComp->GetOwner()->SetLifeSpan(Animation->SequenceLength);
}
