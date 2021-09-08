// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIState.generated.h"


/**
 * 
 */
UENUM(BlueprintType)
enum class AIState : uint8
{
	Patrol = 0,
	Chase = 1,
	Alerted = 2,
	Attack = 3

};
