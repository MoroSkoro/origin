// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/LMAHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LMAWeaponComponent.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ULMAHealthComponent;
class UAnimMontage;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALMADefaultCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
	ULMAHealthComponent* HealthComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULMAWeaponComponent* WeaponComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float YRotation = -75.0f;
	float FOV = 55.0f;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveArmLengthCloser();
	void MoveArmLengthFurther();
	void OnDeath();
	void RotationPlayerOnCursor();
	void OnHealthChanged(float NewHealth);
	void Sprint();
	void StopSprint();

	UPROPERTY()
	float CurrentVelocity;

protected:
	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);
	void UpdateStamina();

public:
	float ArmLength = 1400.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float MinArmLength = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float MaxArmLength = 2000.0f;
	UFUNCTION()
	ULMAHealthComponent* GetHealthComponent() const { return HealthComponent;}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement);
	float Stamina = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement);
	float MinStamina = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement);
	float MaxStamina = 100.0f;
	UPROPERTY();
	bool IsSprint;
	UPROPERTY();
	bool HasStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement);
	float StaminaDrainTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement);
	float StaminaRefillTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement);
	float CurentRefillDelayTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement);
	float DelayBeforeRefill;
};
