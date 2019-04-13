// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "SDTAIController.h"
#include "SDTFleeLocation.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "TimeSplicer.h"

#include "BTTask_MoveToBestFleeLocation.h"




EBTNodeResult::Type UBTTask_MoveToBestFleeLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// CPU Usage time: Detection
	double startTime = FPlatformTime::Seconds();

	if (const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent()) {
		if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner())) {
			// Check if you can execute on this frame
			auto& timeSplicerSingleton = TimeSplicer::instance();
			if (!timeSplicerSingleton.canExecute(aiController->lastUpdateFrame)) return EBTNodeResult::Failed;

			float bestLocationScore = 0.f;
			ASDTFleeLocation* bestFleeLocation = nullptr;

			ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			if (!playerCharacter) {
				return EBTNodeResult::Failed;
			}

			APawn* selfPawn = aiController->GetPawn();
			if (!selfPawn) {
				return EBTNodeResult::Failed;
			}

			for (TActorIterator<ASDTFleeLocation> actorIterator(GetWorld(), ASDTFleeLocation::StaticClass()); actorIterator; ++actorIterator)
			{
				ASDTFleeLocation* fleeLocation = Cast<ASDTFleeLocation>(*actorIterator);
				if (fleeLocation)
				{
					float distToFleeLocation = FVector::Dist(fleeLocation->GetActorLocation(), playerCharacter->GetActorLocation());

					FVector selfToPlayer = playerCharacter->GetActorLocation() - selfPawn->GetActorLocation();
					selfToPlayer.Normalize();

					FVector selfToFleeLocation = fleeLocation->GetActorLocation() - selfPawn->GetActorLocation();
					selfToFleeLocation.Normalize();

					float fleeLocationToPlayerAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(selfToPlayer, selfToFleeLocation)));
					float locationScore = distToFleeLocation + fleeLocationToPlayerAngle * 100.f;

					if (locationScore > bestLocationScore)
					{
						bestLocationScore = locationScore;
						bestFleeLocation = fleeLocation;
					}

					//DrawDebugString(GetWorld(), FVector(0.f, 0.f, 10.f), FString::SanitizeFloat(locationScore), fleeLocation, FColor::Red, 5.f, false);
				}
			}

			if (bestFleeLocation)
			{
				aiController->MoveToLocation(bestFleeLocation->GetActorLocation(), 0.5f, false, true, false, NULL, false);

				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetReachedTargetKeyID(), false);

				double timeTaken = FPlatformTime::Seconds() - startTime;

				// Show CPU Usage time: Detection for 5 seconds
				DrawDebugString(GetWorld(), FVector(0.f, 0.f, 8.f), "player: " + FString::SanitizeFloat(timeTaken) + "s", aiController->GetPawn(), FColor::Green, .5f, false);

				return EBTNodeResult::Succeeded;
			}
		}
	}

    return EBTNodeResult::Failed;
}




