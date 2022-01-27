// Fill out your copyright notice in the Description page of Project Settings.


#include "JLTVTruck.h"
#include "Components/InputComponent.h"

// Sets default values
AJLTVTruck::AJLTVTruck()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJLTVTruck::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJLTVTruck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Force = GetActorForwardVector() * MaxDrivingForce * Throttle;
	FVector Acceleration = Force / Mass;

	Velocity = Velocity + Acceleration * DeltaTime;

	FVector Translation = Velocity * 100 * DeltaTime;
	AddActorWorldOffset(Translation);
}

// Called to bind functionality to input
void AJLTVTruck::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJLTVTruck::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &AJLTVTruck::MoveRight);
	//PlayerInputComponent->BindAxis("LookUp");
	//PlayerInputComponent->BindAxis("LookRight");
}

void AJLTVTruck::MoveForward(float Value) {
	Throttle = Value;
	//Velocity = GetActorForwardVector()* Throttle * Value;
}

