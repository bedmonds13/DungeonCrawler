#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ITakeHit.h"
#include "NiagaraComponent.h"
#include "CharacterStats.h"
#include "DungeonCharacter.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ADungeonCharacter : public ACharacter, public IITakeHit
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADungeonCharacter();

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	UPROPERTY(BlueprintReadWrite, Category = Player)
		class AWeapon* weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite )
		float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxComboDelayAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxAttackDelayAmount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Damage;
	

	/*Animation Montages*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* deathAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* attackAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<UAnimMontage*> attackMontages;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* jumpAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsDead;

	/*Sounds*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundBase* impactSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<USoundBase*> hurtSounds;

	/*Niagara Effects*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	 UNiagaraSystem* impactParticleEffect;
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float maxInputDelayCount;
	UPROPERTY( BlueprintReadOnly,  meta = (AllowPrivateAccess = "true"))
		float inputDelayCount;
	UPROPERTY(VisibleAnywhere,  meta = (AllowPrivateAccess = "true"))
		bool InputAllowed;
	

	UPROPERTY(VisibleAnywhere)
		int hurtCount;
	
protected:


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	

	void Forward(float amount);
	void Back(float amount);
	void Right(float amount);
	void Left(float amount);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Attack(FRotator newRotation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Die();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SpecialMove(FRotator newRotation);

	UFUNCTION(BlueprintCallable)
		void ResetInputTimer();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void AttackImpactEvent();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SpecialImpactEvent();
	
	virtual void TakeHit_Implementation(float damage, ADungeonCharacter* attackingCharacter, AttackType type) override;
		
	UFUNCTION(BlueprintCallable)
		void SetInputAllowed(bool isInputAllowed);

	UFUNCTION(BlueprintCallable)
		void SetCharacterHealth(float SavedHealth);
	
	
	
};
