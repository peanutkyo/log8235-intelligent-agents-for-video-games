// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "SDTUtils.h"

#include "BTTask_IsPlayerPoweredUp.h"




EBTNodeResult::Type UBTTask_IsPlayerPoweredUp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (SDTUtils::IsPlayerPoweredUp(GetWorld())) {
		return EBTNodeResult::Succeeded;
	}

    return EBTNodeResult::Failed;
}




