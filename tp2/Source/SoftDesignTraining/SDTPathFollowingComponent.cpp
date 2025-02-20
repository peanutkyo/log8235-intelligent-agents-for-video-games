// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SDTPathFollowingComponent.h"
#include "SDTUtils.h"
#include "SDTAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "DrawDebugHelpers.h"
#include <Engine/Engine.h>

USDTPathFollowingComponent::USDTPathFollowingComponent(const FObjectInitializer& ObjectInitializer)
{
}

void USDTPathFollowingComponent::FollowPathSegment(float DeltaTime)
{
	Super::FollowPathSegment(DeltaTime);

    const TArray<FNavPathPoint>& points = Path->GetPathPoints();
    const FNavPathPoint& segmentStart = points[MoveSegmentStartIndex];

    if (SDTUtils::HasJumpFlag(segmentStart))
    {
        //update jump
    }
    else
    {
        //update navigation along path
    }
}

void USDTPathFollowingComponent::SetMoveSegment(int32 segmentStartIndex)
{

    Super::SetMoveSegment(segmentStartIndex);

	const TArray<FNavPathPoint>& points = Path->GetPathPoints();
	const FNavPathPoint& segmentStart = points[MoveSegmentStartIndex];

	if (SDTUtils::HasJumpFlag(segmentStart) && FNavMeshNodeFlags(segmentStart.Flags).IsNavLink())
	{
		//Handle starting jump
		Cast<ASDTAIController>(GetOwner())->Jump();
	}
	else
	{
		//Handle normal segments
	}
}

void USDTPathFollowingComponent::UpdatePathSegment()
{
	Super::UpdatePathSegment();
}
