// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SDTBaseAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "AI/Navigation/NavigationSystem.h"

#include "BTTask_MoveToTarget.h"




EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent())
    {
        if (ASDTBaseAIController* aiController = Cast<ASDTBaseAIController>(OwnerComp.GetAIOwner()))
        {
            FVector targetPosition = FVector::ZeroVector;
            if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
            {
                if (AActor* targetActor = Cast<AActor>(MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID())))
                {
                    targetPosition = targetActor->GetActorLocation();
                }
            }
            else if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
            {
                uint8 bbKey = BlackboardKey.GetSelectedKeyID();
                targetPosition = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(bbKey);
            }
            else
            {
                targetPosition = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(aiController->GetTargetPosBBKeyID());
            }

            UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
            NavSys->SimpleMoveToLocation(aiController, targetPosition);

            return EBTNodeResult::Succeeded;
        }
    }    

    return EBTNodeResult::Failed;
}




