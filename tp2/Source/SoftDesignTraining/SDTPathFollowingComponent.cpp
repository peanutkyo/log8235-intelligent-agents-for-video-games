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
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, TEXT("SetMoveSegment"));
	//https://wiki.unrealengine.com/Unreal_Engine_AI_Tutorial_-_1_-_Making_AI_Jump_as_a_Part_of_Path_Following

    Super::SetMoveSegment(segmentStartIndex);

    const TArray<FNavPathPoint>& points = Path->GetPathPoints();

    const FNavPathPoint& segmentStart = points[MoveSegmentStartIndex];

    if (SDTUtils::HasJumpFlag(segmentStart) && FNavMeshNodeFlags(segmentStart.Flags).IsNavLink())
    {
        //Handle starting jump
		//CharacterMoveComp->SetMovementMode(MOVE_Flying);
    }
    else
    {
        //Handle normal segments
		//CharacterMoveComp->SetMovementMode(MOVE_Walking);
    }
}

void USDTPathFollowingComponent::UpdatePathSegment()
{
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, TEXT("UpdatePathSegment"));
	Super::UpdatePathSegment();
}

