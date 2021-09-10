// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CharacterAttackNotify.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DUNGEONCRAWLER_API UCharacterAttackNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
		virtual void Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) override;
	

		UPROPERTY(EditAnywhere)
			USoundBase* impactSound;
		UPROPERTY(EditAnywhere)
			UParticleSystemComponent* impactParticleEffect;


	


};
