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
	bool reachableCollectibleFound = false;
	int i = 0;
	while (!reachableCollectibleFound && i < orderedCollectibles.size()) {
		UNavigationPath* path = UNavigationSystem::FindPathToLocationSynchronously(GetWorld(), GetPawn()->GetActorLocation(), collectibles[orderedCollectibles[i].first]->GetActorLocation());
		if (path != nullptr && path->GetPath().IsValid() && !path->GetPath()->IsPartial()) {
			m_Target = collectibles[i];
			m_PathFollowingComponent->RequestMove(path->GetPath());
			m_ReachedTarget = false;
			reachableCollectibleFound = true;
		}
		i++;
	}
}

void ASDTAIController::GotoSafestFleeSpot(float deltaTime) {
	ASoftDesignTrainingMainCharacter* playerCharacter = Cast<ASoftDesignTrainingMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	TArray<AActor*> fleeSpots;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASDTFleeLocation::StaticClass(), fleeSpots);

	// add collectibles to a vector of pairs data struture
	std::vector<std::pair<int, int>> orderedFleeSpots;
	APawn* pawn = GetPawn();
	for (int i = 0; i < fleeSpots.Num(); i++) {
		orderedFleeSpots.push_back(std::make_pair(i, playerCharacter->GetDistanceTo(fleeSpots[i])));
	}

	// sort the collectibles by their distance from the AI Pawn location
	std::sort(orderedFleeSpots.begin(), orderedFleeSpots.end(), [](auto &left, auto &right) {
		return left.second > right.second;
	});

	UNavigationPath* path = UNavigationSystem::FindPathToLocationSynchronously(GetWorld(), GetPawn()->GetActorLocation(), fleeSpots[orderedFleeSpots[0].first]->GetActorLocation());
	if (path != nullptr && path->GetPath().IsValid() && !path->GetPath()->IsPartial()) {
		m_PathFollowingComponent->RequestMove(path->GetPath());
		m_ReachedTarget = false;
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
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, TEXT("Jump"));
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
    //finish jump before updating AI state
	if (AtJumpSegment) {
		FVector position = GetCharacter()->GetActorLocation();
		jumpDuration += deltaTime;

		if (jumpDuration >= 1) {
			Landing = true;
			InAir = false;
			AtJumpSegment = false;
		}
		else {
			position.Z = initialHeight + JumpApexHeight * JumpCurve->GetFloatValue(jumpDuration);
			GetCharacter()->SetActorLocation(position);
		}
		return;
	}

    APawn* selfPawn = GetPawn();
	if (!selfPawn) {
		return;
	}

    ASoftDesignTrainingMainCharacter* playerCharacter = Cast<ASoftDesignTrainingMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!playerCharacter) {
		return;
	}

	if (playerCharacter->IsPoweredUp()) {
		// fleeing behavior
		IsFleeing = true;
	}
	else {
		IsFleeing = false;

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

		//Set behavior based on hit
		AActor* target = detectionHit.GetActor();
		if (target && target->IsA(ACharacter::StaticClass())) {
			UNavigationPath* path = UNavigationSystem::FindPathToLocationSynchronously(GetWorld(), GetPawn()->GetActorLocation(), target->GetActorLocation());
			if (path != nullptr && path->GetPath().IsValid() && !path->GetPath()->IsPartial()) {
				m_Target = target;
				m_PathFollowingComponent->RequestMove(path->GetPath());
				m_ReachedTarget = false;
			}
		}

		DrawDebugCapsule(GetWorld(), detectionStartLocation + m_DetectionCapsuleHalfLength * selfPawn->GetActorForwardVector(), m_DetectionCapsuleHalfLength, m_DetectionCapsuleRadius, selfPawn->GetActorQuat() * selfPawn->GetActorUpVector().ToOrientationQuat(), FColor::Blue);
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
