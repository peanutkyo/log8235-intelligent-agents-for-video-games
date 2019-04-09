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

#include "BTTask_IsPlayerUnseen.h"




EBTNodeResult::Type UBTTask_IsPlayerUnseen::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner())) {
		//finish jump before updating AI state
		if (aiController->AtJumpSegment)
			return EBTNodeResult::Failed;

		APawn* pawn = aiController->GetPawn();
		FVector detectionStartLocation = pawn->GetActorLocation() + pawn->GetActorForwardVector() * aiController->m_DetectionCapsuleForwardStartingOffset;
		FVector detectionEndLocation = detectionStartLocation + pawn->GetActorForwardVector() * aiController->m_DetectionCapsuleHalfLength * 2;

		TArray<TEnumAsByte<EObjectTypeQuery>> detectionTraceObjectTypes;
		detectionTraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(COLLISION_PLAYER));

		TArray<FHitResult> allDetectionHits;
		GetWorld()->SweepMultiByObjectType(allDetectionHits, detectionStartLocation, detectionEndLocation, FQuat::Identity, detectionTraceObjectTypes, FCollisionShape::MakeSphere(aiController->m_DetectionCapsuleRadius));

		for (const FHitResult& hit : allDetectionHits)
		{
			if (UPrimitiveComponent* component = hit.GetComponent())
			{
				if (component->GetCollisionObjectType() == COLLISION_PLAYER)
				{
					OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_String>(aiController->GetDebugStateKeyID(), "Chase");
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}

    return EBTNodeResult::Failed;
}




