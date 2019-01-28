// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "DrawDebugHelpers.h"
#include "PhysicsHelpers.h"
#include "SDTCollectible.h"

void ASDTAIController::Tick(float deltaTime)
{
	auto world = GetWorld();
	auto physicsHelper = PhysicsHelpers(world);

	DrawVisionCone(world, GetPawn(), GetPawn()->GetActorForwardVector(), m_visionAngle);
	TArray<FOverlapResult> detectedItems = CollectTargetActorsInFrontOfCharacter(GetPawn(), physicsHelper);

	for (FOverlapResult item : detectedItems)
	{
		if(item.GetActor()->IsA(ASDTCollectible::StaticClass()))
		{
			FVector2D collectible = FVector2D(item.GetActor()->GetActorLocation());

			MoveToTarget(collectible, m_maxSpeed, deltaTime);
		}
	}
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
