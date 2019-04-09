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

#include "BTTask_FindNearestCollectible.h"




EBTNodeResult::Type UBTTask_FindNearestCollectible::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner())) {
		float closestSqrCollectibleDistance = 18446744073709551610.f;
		ASDTCollectible* closestCollectible = nullptr;

		TArray<AActor*> foundCollectibles;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASDTCollectible::StaticClass(), foundCollectibles);

		while (foundCollectibles.Num() != 0)
		{
			int index = FMath::RandRange(0, foundCollectibles.Num() - 1);

			ASDTCollectible* collectibleActor = Cast<ASDTCollectible>(foundCollectibles[index]);
			if (!collectibleActor)
				return EBTNodeResult::Failed;

			if (!collectibleActor->IsOnCooldown())
			{
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(aiController->GetTargetPosBBKeyID(), collectibleActor->GetTargetLocation());
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_String>(aiController->GetDebugStateKeyID(), "Collect");
				return EBTNodeResult::Succeeded;
			}
			else
			{
				foundCollectibles.RemoveAt(index);
			}
		}
	}

    return EBTNodeResult::Failed;
}




