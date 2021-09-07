// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DungeonCharacterAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API UDungeonCharacterAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float duration  ) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
