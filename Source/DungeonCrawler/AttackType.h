// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class AttackType : uint8
{
	Light = 0,
	Medium = 1,
	Heavy = 2
	
};
