// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "SDTCollectible.h"
#include "SDTFleeLocation.h"
#include "SDTPathFollowingComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "UnrealMathUtility.h"
#include "SDTUtils.h"
#include "EngineUtils.h"
#include <Engine/Engine.h>
#include <AI/Navigation/NavigationPath.h>
#include <vector>
#include <algorithm>
#include "SoftDesignTrainingMainCharacter.h"


ASDTAIController::ASDTAIController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USDTPathFollowingComponent>(TEXT("PathFollowingComponent")))
{
}

void ASDTAIController::GoToBestTarget(float deltaTime)
{
    //Move to target depending on current behavior
	if (IsFleeing) {
		GotoSafestFleeSpot(deltaTime);
	}
	else {
		GotoClosestCollectible(deltaTime);
	}	
}

void ASDTAIController::GotoClosestCollectible(float deltaTime) {
	// Find the nearest collectible target
	TArray<AActor*> collectibles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASDTCollectible::StaticClass(), collectibles);

	// add collectibles to a vector of pairs data struture
	std::vector<std::pair<int, int>> orderedCollectibles;
	APawn* pawn = GetPawn();
	for (int i = 0; i < collectibles.Num(); i++) {
		if (!Cast<ASDTCollectible>(collectibles[i])->IsOnCooldown()) {
			orderedCollectibles.push_back(std::make_pair(i, pawn->GetDistanceTo(collectibles[i])));
		}
	}

	// sort the collectibles by their distance from the AI Pawn location
	std::sort(orderedCollectibles.begin(), orderedCollectibles.end(), [](auto &left, auto &right) {
		return left.second < right.second;
	});

	// Set as target the first closest and reachable collectible
	int i = 0;
	EPathFollowingRequestResult::Type result;
	do {
		result = MoveToLocation(collectibles[orderedCollectibles[i].first]->GetActorLocation());
		i++;
	}
	while (result != EPathFollowingRequestResult::RequestSuccessful || i >= collectibles.Num());

	if (result == EPathFollowingRequestResult::RequestSuccessful) {
		OnMoveToTarget();
	}
}

void ASDTAIController::GotoSafestFleeSpot(float deltaTime) {
	ASoftDesignTrainingMainCharacter* playerCharacter = Cast<ASoftDesignTrainingMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	TArray<AActor*> fleeSpots;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASDTFleeLocation::StaticClass(), fleeSpots);

	// add fleespots to a vector of pairs data struture
	std::vector<std::pair<int, int>> orderedFleeSpots;
	APawn* pawn = GetPawn();
	for (int i = 0; i < fleeSpots.Num(); i++) {
		orderedFleeSpots.push_back(std::make_pair(i, playerCharacter->GetDistanceTo(fleeSpots[i])));
	}

	// sort the fleespots by their distance from the player location
	std::sort(orderedFleeSpots.begin(), orderedFleeSpots.end(), [](auto &left, auto &right) {
		return left.second > right.second;
	});

	// Set as target the furthest flee spot from the player
	int i = 0;
	EPathFollowingRequestResult::Type result;
	do {
		result = MoveToLocation(fleeSpots[orderedFleeSpots[i].first]->GetActorLocation());
		i++;
	} while (result != EPathFollowingRequestResult::RequestSuccessful || i >= fleeSpots.Num());

	if (result == EPathFollowingRequestResult::RequestSuccessful) {
		OnMoveToTarget();
	}
}

void ASDTAIController::OnMoveToTarget()
{
    m_ReachedTarget = false;
}

void ASDTAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    m_ReachedTarget = true;
}

void ASDTAIController::Jump() {
	if (AtJumpSegment) return;

	initialHeight = GetCharacter()->GetActorLocation().Z;
	jumpDuration = 0;
	InAir = true;
	Landing = false;
	AtJumpSegment = true;
}

void ASDTAIController::ShowNavigationPath()
{
    //Show current navigation path DrawDebugLine and DrawDebugSphere
	if (m_PathFollowingComponent->GetPath().IsValid()) {
		const TArray<FNavPathPoint>& points = m_PathFollowingComponent->GetPath()->GetPathPoints();

		FVector startPoint = points[0].Location;
		FVector endPoint;
		for (FNavPathPoint point : points) {
			endPoint = point.Location;
			DrawDebugLine(GetWorld(), startPoint, endPoint, FColor::Green);
			DrawDebugSphere(GetWorld(), endPoint, 10.0f, 12, FColor::Red);
			startPoint = endPoint;
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, TEXT("Invalid Path"));
	}
}

void ASDTAIController::ChooseBehavior(float deltaTime)
{
    UpdatePlayerInteraction(deltaTime);
}

void ASDTAIController::UpdatePlayerInteraction(float deltaTime)
{
	APawn* selfPawn = GetPawn();
	if (!selfPawn) {
		return;
	}

    //finish jump before updating AI state
	if (AtJumpSegment) {
		FVector position = selfPawn->GetActorLocation();
		jumpDuration += deltaTime;

		float min, max;
		JumpCurve->GetTimeRange(min, max);
		if (jumpDuration >= max) {
			// jump finished
			Landing = true;
			InAir = false;
			AtJumpSegment = false;
		}
		else {
			// change ai jump height following the provided jump curve
			position.Z = initialHeight + JumpApexHeight * JumpCurve->GetFloatValue(jumpDuration);
			GetCharacter()->SetActorLocation(position);
		}
		return;
	}

    ASoftDesignTrainingMainCharacter* playerCharacter = Cast<ASoftDesignTrainingMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!playerCharacter) {
		return;
	}

	// trigger normal behavior (chase player or find collectibles)
	if (IsFleeing && !playerCharacter->IsPoweredUp()) {
		IsFleeing = false;
		AIStateInterrupted();
	}

	// trigger flee behavior
	if (!IsFleeing && playerCharacter->IsPoweredUp()) {
		IsFleeing = true;
		AIStateInterrupted();
	}

	// chase player behavior
	FVector detectionStartLocation = selfPawn->GetActorLocation() + selfPawn->GetActorForwardVector() * m_DetectionCapsuleForwardStartingOffset;
	FVector detectionEndLocation = detectionStartLocation + selfPawn->GetActorForwardVector() * m_DetectionCapsuleHalfLength * 2;

	TArray<TEnumAsByte<EObjectTypeQuery>> detectionTraceObjectTypes;
	detectionTraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(COLLISION_COLLECTIBLE));
	detectionTraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(COLLISION_PLAYER));

	TArray<FHitResult> allDetectionHits;
	GetWorld()->SweepMultiByObjectType(allDetectionHits, detectionStartLocation, detectionEndLocation, FQuat::Identity, detectionTraceObjectTypes, FCollisionShape::MakeSphere(m_DetectionCapsuleRadius));

	FHitResult detectionHit;
	GetHightestPriorityDetectionHit(allDetectionHits, detectionHit);

	DrawDebugCapsule(GetWorld(), detectionStartLocation + m_DetectionCapsuleHalfLength * selfPawn->GetActorForwardVector(), m_DetectionCapsuleHalfLength, m_DetectionCapsuleRadius, selfPawn->GetActorQuat() * selfPawn->GetActorUpVector().ToOrientationQuat(), FColor::Blue);

	if (IsFleeing) return;

	//Set behavior based on hit
	AActor* target = detectionHit.GetActor();
	if (target && target->IsA(ACharacter::StaticClass())) {
		if (MoveToLocation(target->GetActorLocation()) == EPathFollowingRequestResult::RequestSuccessful) {
			OnMoveToTarget();
		}
	}
}

void ASDTAIController::GetHightestPriorityDetectionHit(const TArray<FHitResult>& hits, FHitResult& outDetectionHit)
{
    for (const FHitResult& hit : hits)
    {
        if (UPrimitiveComponent* component = hit.GetComponent())
        {
            if (component->GetCollisionObjectType() == COLLISION_PLAYER)
            {
                //we can't get more important than the player
                outDetectionHit = hit;
                return;
            }
            else if (component->GetCollisionObjectType() == COLLISION_COLLECTIBLE)
            {
                outDetectionHit = hit;
            }
        }
    }
}

void ASDTAIController::AIStateInterrupted()
{
    StopMovement();
    m_ReachedTarget = true;
}
