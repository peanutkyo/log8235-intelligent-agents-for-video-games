// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"

#include "BTTask_MoveToBestFleeLocation.h"




EBTNodeResult::Type UBTTask_MoveToBestFleeLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner())) {
		if (aiController->IsTargetReached()) {
			aiController->MoveToBestFleeLocation();
			return EBTNodeResult::Succeeded;
		}
	}

    return EBTNodeResult::Failed;
}




