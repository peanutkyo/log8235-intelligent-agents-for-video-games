// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "AI/Navigation/NavigationSystem.h"
#include "SDTUtils.h"
#include "DrawDebugHelpers.h"
#include "SDTPathFollowingComponent.h"

#include "BTTask_DisplayDebug.h"




EBTNodeResult::Type UBTTask_DisplayDebug::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/*if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner())) {
		APawn* pawn = aiController->GetPawn();
		FString debugString = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_String>(aiController->GetDebugStateKeyID());
		FVector detectionStartLocation = pawn->GetActorLocation() + pawn->GetActorForwardVector() * aiController->m_DetectionCapsuleForwardStartingOffset;
		FVector detectionEndLocation = detectionStartLocation + pawn->GetActorForwardVector() * aiController->m_DetectionCapsuleHalfLength * 2;

		// Diplay state
		DrawDebugString(GetWorld(), FVector(0.f, 0.f, 5.f), debugString, aiController->GetPawn(), FColor::Orange, 0.f, false);

		// Display vision capsule
		DrawDebugCapsule(GetWorld(), detectionStartLocation + aiController->m_DetectionCapsuleHalfLength * pawn->GetActorForwardVector(), aiController->m_DetectionCapsuleHalfLength, aiController->m_DetectionCapsuleRadius, pawn->GetActorQuat() * pawn->GetActorUpVector().ToOrientationQuat(), FColor::Blue);

		// Display navigation path
		if (UPathFollowingComponent* pathFollowingComponent = aiController->GetPathFollowingComponent())
		{
			if (pathFollowingComponent->HasValidPath())
			{
				const FNavPathSharedPtr path = pathFollowingComponent->GetPath();
				TArray<FNavPathPoint> pathPoints = path->GetPathPoints();

				for (int i = 0; i < pathPoints.Num(); ++i)
				{
					DrawDebugSphere(GetWorld(), pathPoints[i].Location, 10.f, 8, FColor::Yellow);

					if (i != 0)
					{
						DrawDebugLine(GetWorld(), pathPoints[i].Location, pathPoints[i - 1].Location, FColor::Yellow);
					}
				}
			}
		}
	}*/

    return EBTNodeResult::Succeeded;
}




