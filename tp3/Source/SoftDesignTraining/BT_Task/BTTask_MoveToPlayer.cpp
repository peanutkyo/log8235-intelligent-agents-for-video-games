// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "AI/Navigation/NavigationSystem.h"

#include "BTTask_MoveToPlayer.h"




EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ASDTAIController* aiController = Cast<ASDTAIController>(OwnerComp.GetAIOwner())) {
		//OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetReachedTargetKeyID(), false);
		/*aiController->SetTargetReached(false);
		aiController->MoveToPlayer();
		return EBTNodeResult::Succeeded;*/






		ACharacter * playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (!playerCharacter)
			return EBTNodeResult::Failed;

		aiController->MoveToActor(playerCharacter, 0.5f, false, true, true, NULL, false);
		//aiController->SetTargetReached(false);
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetReachedTargetKeyID(), false);

		return EBTNodeResult::Succeeded;
	}

    return EBTNodeResult::Failed;
}




