// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"


DECLARE_MULTICAST_DELEGATE(FOutOfBulletsDelegat);

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

UCLASS()
class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALMABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float RateOfFire = 0.1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float BulletSpread = 1.2;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();
	void StopFire();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;
	void Shoot();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon AmmoWeapon{30, 0, true};
	UPROPERTY()
	FAmmoWeapon CurrentAmmoWeapon;
	void DecrementBullets();
	bool IsCurrentClipEmpty() const;
	bool IsCurrentClipFull() const;
	void ChangeClip();
	FOutOfBulletsDelegat OutOfBulletsDelegat;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool BaseAnimReloading = true;

private:
	FTimerHandle WeaponShootTimer;
};
