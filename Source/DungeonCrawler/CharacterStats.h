#pragma once

#include "Engine.h"
#include "DungeonCharacter.h"
#include "CharacterStats.generated.h"



USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf <ADungeonCharacter> playerSelectedCharacter;
};


