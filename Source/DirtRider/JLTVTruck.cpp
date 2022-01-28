// Fill out your copyright notice in the Description page of Project Settings.


#include "JLTVTruck.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"

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
	Force += GetAirResistance();
	Force += GetRollingResistance();
	FVector Acceleration = Force / Mass;

	Velocity = Velocity + Acceleration * DeltaTime;

	ApplyRotation(DeltaTime);
	UpdateLocationFromVelocity(DeltaTime);
}

FVector AJLTVTruck::GetAirResistance() {
	return - Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient;
}

FVector AJLTVTruck::GetRollingResistance() {
	//UE_LOG(LogTemp, Warning, TEXT("Gravity %f"), GetWorld()->GetGravityZ());
	float AccelerationDueToGravity = -GetWorld()->GetGravityZ() / 100;
	float NormalForce = Mass * AccelerationDueToGravity;
	return -Velocity.GetSafeNormal() * RollingResistanceCoefficieant * NormalForce;
}

void AJLTVTruck::ApplyRotation(float DeltaTime)
{
	float DeltaLocation = FVector::DotProduct(GetActorForwardVector(), Velocity) * DeltaTime;
	float RotationAngle = DeltaLocation / MinTurnRadius * SteeringThrow;
	FQuat RotationDelta(GetActorUpVector(), RotationAngle);
	Velocity = RotationDelta.RotateVector(Velocity);
	AddActorWorldRotation(RotationDelta);
}

void AJLTVTruck::UpdateLocationFromVelocity(float DeltaTime)
{
	FVector Translation = Velocity * 100 * DeltaTime;

	FHitResult OutHitResult;
	AddActorWorldOffset(Translation, true, &OutHitResult);
	if (OutHitResult.IsValidBlockingHit()) { Velocity = FVector::ZeroVector; }
}

// Called to bind functionality to input
void AJLTVTruck::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJLTVTruck::Server_MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJLTVTruck::MoveRight);
	//PlayerInputComponent->BindAxis("LookUp");
	//PlayerInputComponent->BindAxis("LookRight");
}

void AJLTVTruck::Server_MoveForward_Implementation(float Value) {
	Throttle = Value;
	//Velocity = GetActorForwardVector()* Throttle * Value;
}

bool AJLTVTruck::Server_MoveForward_Validate(float Value) {
	return true;
}

void AJLTVTruck::MoveRight(float Value) {
	SteeringThrow = Value;
}

	

