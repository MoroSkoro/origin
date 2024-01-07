// Fill out your copyright notice in the Description page of Project Settings.


#include "CppHubActor.h"
#include "TimerManager.h"
#include "CppBaseActor.h"

// Sets default values
ACppHubActor::ACppHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACppHubActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ACppHubActor::OnTimeToSpawn, SpawnTimerRate, true);
}

// Called every frame
void ACppHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//OnTimeToSpawn();
}

void ACppHubActor::OnTimeToSpawn() {
	if (++CurrentTimerCount <= TotalCount) {
		const FVector Location = GetActorLocation() + FVector(FMath::FRandRange(1400.0f, 1700.0f), FMath::FRandRange(350.0f, 1300.0f), 5.0f);
		const FRotator Rotation = FRotator::ZeroRotator;
		ACppBaseActor* SpawnObject = GetWorld()->SpawnActor<ACppBaseActor>(CppClass, Location, Rotation);
		if (SpawnObject) {
			SpawnedObjects.Add(SpawnObject);
		}
	}
	else {
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		for (int i = TotalCount; i >= 1; --i) {
			GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ACppHubActor::OnTimeToDestroy, DestroyTimerRate, true);
		}
	}
}

void ACppHubActor::OnTimeToDestroy() {
	if (!SpawnedObjects.IsEmpty()) {
		SpawnedObjects.Top()->Destroy();
		SpawnedObjects.Pop();
	}
	else {
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
	}
}