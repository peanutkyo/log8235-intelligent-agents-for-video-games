// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "SDTCollectible.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "AI/Navigation/NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "TimeSplicer.h"
#include "Engine.h"

#include "BTTask_MoveToRandomCollectible.h"




EBTNodeResult::Type UBTTask_MoveToRandomCollectible::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// CPU Usage time: Detection
	double startTime = FPlatformTime::Seconds();

	if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner())) {
		// Check if you can execute on this frame
		if (!(aiController->timeSplicer->canExecute(aiController->lastUpdateFrame))) return EBTNodeResult::Failed;

		if (OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Bool>(aiController->GetReachedTargetKeyID())) {
			float closestSqrCollectibleDistance = 18446744073709551610.f;
			ASDTCollectible* closestCollectible = nullptr;

			TArray<AActor*> foundCollectibles;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASDTCollectible::StaticClass(), foundCollectibles);

			while (foundCollectibles.Num() != 0)
			{
				int index = FMath::RandRange(0, foundCollectibles.Num() - 1);

				ASDTCollectible* collectibleActor = Cast<ASDTCollectible>(foundCollectibles[index]);
				if (!collectibleActor) {
					return EBTNodeResult::Failed;
				}

				if (!collectibleActor->IsOnCooldown())
				{
					aiController->MoveToLocation(foundCollectibles[index]->GetActorLocation(), 0.5f, false, true, true, NULL, false);

					OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetReachedTargetKeyID(), false);

					double timeTaken = FPlatformTime::Seconds() - startTime;

					// Show CPU Usage time: Detection for 5 seconds
					DrawDebugString(GetWorld(), FVector(0.f, 0.f, 8.f), "collectible: " + FString::SanitizeFloat(timeTaken) + "s", aiController->GetPawn(), FColor::Orange, .5f, false);

					return EBTNodeResult::Succeeded;
				}
				else
				{
					foundCollectibles.RemoveAt(index);
				}
			}

		}
	}

    return EBTNodeResult::Failed;
}




