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

ASDTAIController::ASDTAIController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USDTPathFollowingComponent>(TEXT("PathFollowingComponent")))
{
}

void ASDTAIController::GoToBestTarget(float deltaTime)
{
    //Move to target depending on current behavior


	// Find the nearest collectible target
	TArray<AActor*> collectibles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASDTCollectible::StaticClass(), collectibles);

	int closestIndex = 0;
	float shortestDistance = 9999.f;
	for (int i = 0; i < collectibles.Num(); i++) {
		float distance = GetPawn()->GetDistanceTo(collectibles[i]);
		
		if (!Cast<ASDTCollectible>(collectibles[i])->IsOnCooldown() && distance < shortestDistance) {
			closestIndex = i;
			shortestDistance = distance;
		}
	}

	m_Target = collectibles[closestIndex];

	// Define path and pass it to PathFollowingComponent
	UNavigationPath* path = UNavigationSystem::FindPathToLocationSynchronously(GetWorld(), GetPawn()->GetActorLocation(), m_Target->GetActorLocation());
	if (path != nullptr && path->GetPath().IsValid() && !path->GetPath()->IsPartial()) {
		m_PathFollowingComponent->RequestMove(path->GetPath());
		m_ReachedTarget = false;
	}
}

void ASDTAIController::OnMoveToTarget()
{
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, TEXT("OnMoveToTarget"));
    m_ReachedTarget = false;
}

void ASDTAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("OnMoveCompleted"));

    m_ReachedTarget = true;
}

void ASDTAIController::ShowNavigationPath()
{
	/* TODO working example DELETE WHEN DONE
	//const TArray<FNavPathPoint>& points = m_PathFollowingComponent->GetPath()->GetPathPoints();
	TArray<FNavPathPoint>& points = UNavigationSystem::FindPathToLocationSynchronously(GetWorld(), GetPawn()->GetActorLocation(), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation())->GetPath()->GetPathPoints();

	FVector startPoint = points[0].Location;
	FVector endPoint;
	for (FNavPathPoint point : points) {
		endPoint = point.Location;
		DrawDebugLine(GetWorld(), startPoint, endPoint, FColor::Green);
		DrawDebugSphere(GetWorld(), endPoint, 10.0f, 12, FColor::Red);
		startPoint = endPoint;
	}
	*/


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
    if (AtJumpSegment)
        return;

    APawn* selfPawn = GetPawn();
    if (!selfPawn)
        return;

    ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!playerCharacter)
        return;

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

    DrawDebugCapsule(GetWorld(), detectionStartLocation + m_DetectionCapsuleHalfLength * selfPawn->GetActorForwardVector(), m_DetectionCapsuleHalfLength, m_DetectionCapsuleRadius, selfPawn->GetActorQuat() * selfPawn->GetActorUpVector().ToOrientationQuat(), FColor::Blue);
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