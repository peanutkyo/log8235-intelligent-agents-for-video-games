// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "DrawDebugHelpers.h"
#include "PhysicsHelpers.h"
#include "SDTCollectible.h"
#include "Engine.h"
#include <chrono>
#include <random>

void ASDTAIController::Tick(float deltaTime)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	UWorld* world = GetWorld();
	APawn* pawn = GetPawn();

	// should be a serializefield kinda
	const float distanceToObstacle = 200.f;
	const float maxSpeed = 1.f;
	const FVector acceleration = FVector(0.1f);

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	FHitResult losHit;
	FCollisionQueryParams queryParams = FCollisionQueryParams();
	queryParams.AddIgnoredActor(pawn);
	bool isGonnaCollide = world->LineTraceSingleByObjectType
	(
		losHit,
		pawn->GetActorLocation(),
		pawn->GetActorLocation() + distanceToObstacle * pawn->GetActorForwardVector(),
		TraceObjectTypes, queryParams
	);

	if (isGonnaCollide)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Salim est beau."));

		// TODO: Switch randomly between four basic orientations ?
		// TODO: Do it slowly.

		FRotator rotator = FVector(0.f, 0.5f, 0.f).ToOrientationRotator();
		//FRotator rotator = FVector(0.f, -0.5f, 0.f).ToOrientationRotator();
		//FRotator rotator = FVector(0.f, -1.f, 0.f).ToOrientationRotator();
		//FRotator rotator = FVector(0.f, 1.f, 0.f).ToOrientationRotator();
		pawn->AddActorWorldRotation(rotator, true);

		pawn->AddMovementInput(pawn->GetActorForwardVector(), maxSpeed, true);
		//pawn->AddMovementInput(pawn->GetActorForwardVector(), m_currentSpeed.Size(), true);
	}
	else
	{
		IncreaseSpeed(acceleration, maxSpeed, deltaTime);
		pawn->AddMovementInput(pawn->GetActorForwardVector(), maxSpeed, true);
		//pawn->AddMovementInput(pawn->GetActorForwardVector(), m_currentSpeed.Size(), true);
	}
}

FVector ASDTAIController::IncreaseSpeed(FVector acceleration, float maxSpeed, float deltaTime) 
{
	FVector newSpeed = m_currentSpeed + acceleration * deltaTime;

	// need to debug the speed
	if (newSpeed.Size() > maxSpeed) 
	{
		newSpeed.Normalize(); // vecteur unitaire
		newSpeed *= maxSpeed;
	}

	return newSpeed;
}

FVector ASDTAIController::DecreaseSpeed(FVector acceleration, float maxSpeed, float deltaTime)
{
	FVector newSpeed = m_currentSpeed - acceleration * deltaTime;
	if (newSpeed.Size() < m_currentSpeed.Size())
	{
		m_currentSpeed = FVector(0.1f);
	}

	return newSpeed;
}

bool ASDTAIController::MoveToTarget(FVector2D target, float targetSpeed, float deltaTime)
{
	APawn* pawn = GetPawn();
	FVector const pawnPosition(pawn->GetActorLocation());
	FVector2D const toTarget = target - FVector2D(pawnPosition);
	FVector2D const displacement = FMath::Min(toTarget.Size(), FMath::Min(m_maxSpeed, targetSpeed) * deltaTime) * toTarget.GetSafeNormal();
	pawn->SetActorLocation(pawnPosition + FVector(displacement, 0.f), true);
	pawn->SetActorRotation(FVector(displacement, 0.f).ToOrientationQuat());
	return toTarget.Size() < FMath::Min(m_maxSpeed, targetSpeed) * deltaTime;
}

void ASDTAIController::MoveTowardsDirection(FVector2D direction, float speed, float deltaTime)
{
	APawn* pawn = GetPawn();
	FVector const pawnPosition(pawn->GetActorLocation());
	FVector2D const displacement = FMath::Min(m_maxSpeed, speed) * deltaTime * direction.GetSafeNormal();
	
	pawn->SetActorLocation(pawnPosition + FVector(displacement, 0.f), true);
	pawn->SetActorRotation(FVector(direction, 0.f).ToOrientationQuat());
}

void ASDTAIController::DrawVisionCone(UWorld* world, APawn* pawn, FVector const& dir, float angle) const
{
	DrawDebugCone(world, pawn->GetActorLocation(), dir, 5000.0f, angle, angle, 50, FColor::Green, false, -1.0f, 0, 5.0f);
}

TArray<FOverlapResult> ASDTAIController::CollectTargetActorsInFrontOfCharacter(APawn const* pawn, PhysicsHelpers& physicHelper) const
{
	TArray<FOverlapResult> outResults;
	physicHelper.SphereOverlap(pawn->GetActorLocation() + pawn->GetActorForwardVector() * 750.0f, 750.0f, outResults, true);
	return outResults;
}
