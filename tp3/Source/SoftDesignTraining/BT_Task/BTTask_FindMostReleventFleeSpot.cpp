// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "SDTFleeLocation.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"

#include "BTTask_FindMostReleventFleeSpot.h"




EBTNodeResult::Type UBTTask_FindMostReleventFleeSpot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner())) {
		float bestLocationScore = 0.f;
		ASDTFleeLocation* bestFleeLocation = nullptr;

		ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (!playerCharacter)
			return EBTNodeResult::Failed;

		for (TActorIterator<ASDTFleeLocation> actorIterator(GetWorld(), ASDTFleeLocation::StaticClass()); actorIterator; ++actorIterator)
		{
			ASDTFleeLocation* fleeLocation = Cast<ASDTFleeLocation>(*actorIterator);
			if (fleeLocation)
			{
				float distToFleeLocation = FVector::Dist(fleeLocation->GetActorLocation(), playerCharacter->GetActorLocation());

				FVector selfToPlayer = playerCharacter->GetActorLocation() - aiController->GetPawn()->GetActorLocation();
				selfToPlayer.Normalize();

				FVector selfToFleeLocation = fleeLocation->GetActorLocation() - aiController->GetPawn()->GetActorLocation();
				selfToFleeLocation.Normalize();

				float fleeLocationToPlayerAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(selfToPlayer, selfToFleeLocation)));
				float locationScore = distToFleeLocation + fleeLocationToPlayerAngle * 100.f;

				if (locationScore > bestLocationScore)
				{
					bestLocationScore = locationScore;
					bestFleeLocation = fleeLocation;
				}

				DrawDebugString(GetWorld(), FVector(0.f, 0.f, 10.f), FString::SanitizeFloat(locationScore), fleeLocation, FColor::Red, 5.f, false);
			}
		}

		if (bestFleeLocation)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(aiController->GetTargetPosBBKeyID(), bestFleeLocation->GetTargetLocation());
			return EBTNodeResult::Succeeded;
		}
	}

    return EBTNodeResult::Failed;
}




