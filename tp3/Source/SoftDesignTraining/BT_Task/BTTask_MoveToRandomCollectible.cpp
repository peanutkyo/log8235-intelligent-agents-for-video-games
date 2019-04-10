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

#include "BTTask_MoveToRandomCollectible.h"




EBTNodeResult::Type UBTTask_MoveToRandomCollectible::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner())) {
		if (aiController->IsTargetReached()) {
			aiController->MoveToRandomCollectible();
			return EBTNodeResult::Succeeded;
		}
	}

    return EBTNodeResult::Failed;
}




