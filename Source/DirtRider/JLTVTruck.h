// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "JLTVTruck.generated.h"

UCLASS()
class DIRTRIDER_API AJLTVTruck : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJLTVTruck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Mass of the truck (kg)
	UPROPERTY(EditAnywhere)
		float Mass = 1000;

	//The force applied to the car in full throttle
	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 10000;

	void MoveForward(float Value);
	FVector Velocity;
	float Throttle;
};
