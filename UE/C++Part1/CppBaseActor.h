// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppBaseActor.generated.h"

UCLASS()
class CIBERG_API ACppBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACppBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	FString PlayerName = GetName();

	UPROPERTY(EditInstanceOnly)
	int EnemyNum = 20;

	UPROPERTY(EditInstanceOnly)
	bool IsAlive = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void ShowActorInformation();
};
