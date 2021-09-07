// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CharacterAttackNotify.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API UCharacterAttackNotify : public UAnimNotify
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	USoundBase* impactSound;

	


};
