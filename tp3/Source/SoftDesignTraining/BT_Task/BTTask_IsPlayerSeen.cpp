// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "SDTUtils.h"
#include "DrawDebugHelpers.h"
#include "TimeSplicer.h"
#include "AiGroupManager.h"

#include "BTTask_IsPlayerSeen.h"




EBTNodeResult::Type UBTTask_IsPlayerSeen::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// CPU Usage time: Detection
	double startTime = FPlatformTime::Seconds();

	if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner())) {
		// Check if you can execute on this frame
		auto& timeSplicerSingleton = TimeSplicer::instance();
		if (!timeSplicerSingleton.canExecute(aiController->lastUpdateFrame)) return EBTNodeResult::Failed;

		//finish jump before updating AI state
		if (aiController->AtJumpSegment) {
			return EBTNodeResult::Failed;
		}

		APawn* selfPawn = aiController->GetPawn();
		if (!selfPawn) {
			return EBTNodeResult::Failed;
		}

		ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (!playerCharacter) {
			return EBTNodeResult::Failed;
		}

		FVector detectionStartLocation = selfPawn->GetActorLocation() + selfPawn->GetActorForwardVector() * aiController->m_DetectionCapsuleForwardStartingOffset;
		FVector detectionEndLocation = detectionStartLocation + selfPawn->GetActorForwardVector() * aiController->m_DetectionCapsuleHalfLength * 2;

		TArray<TEnumAsByte<EObjectTypeQuery>> detectionTraceObjectTypes;
		detectionTraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(COLLISION_PLAYER));

		TArray<FHitResult> allDetectionHits;
		GetWorld()->SweepMultiByObjectType(allDetectionHits, detectionStartLocation, detectionEndLocation, FQuat::Identity, detectionTraceObjectTypes, FCollisionShape::MakeSphere(aiController->m_DetectionCapsuleRadius));

		for (const FHitResult& hit : allDetectionHits)
		{
			if (UPrimitiveComponent* component = hit.GetComponent())
			{
				if (component && component->GetCollisionObjectType() == COLLISION_PLAYER)
				{
					OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetReachedTargetKeyID(), true);

					if (OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Bool>(aiController->GetLostPlayerSightKeyID())) {
						TArray<AActor*> list;
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAiGroupManager::StaticClass(), list);
						AAiGroupManager* aiGroupManager = Cast<AAiGroupManager>(list[0]);
						aiGroupManager->AddAIActorToGroup(aiController);

						OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetLostPlayerSightKeyID(), false);
					}

					double timeTaken = FPlatformTime::Seconds() - startTime;
					
					// Show CPU Usage time: Detection for 5 seconds
					DrawDebugString(GetWorld(), FVector(0.f, 0.f, 8.f), "player: " + FString::SanitizeFloat(timeTaken) + "s", aiController->GetPawn(), FColor::Green, .5f, false);

					return EBTNodeResult::Succeeded;
				}
			}
		}

		if (!OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Bool>(aiController->GetLostPlayerSightKeyID())) {
			TArray<AActor*> list;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAiGroupManager::StaticClass(), list);
			AAiGroupManager* aiGroupManager = Cast<AAiGroupManager>(list[0]);
			aiGroupManager->RemoveAIActorFromGroup(aiController);

			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetLostPlayerSightKeyID(), true);
		}
	}

    return EBTNodeResult::Failed;
}




