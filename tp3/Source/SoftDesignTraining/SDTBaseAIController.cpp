// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SDTBaseAIController.h"
#include "SoftDesignTrainingCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


ASDTBaseAIController::ASDTBaseAIController(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    m_ReachedTarget = true;

	// BT_AI
	m_behaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	m_blackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void ASDTBaseAIController::Tick(float deltaTime)
{
    Super::Tick(deltaTime);

    /*UpdatePlayerInteraction(deltaTime);

    if (m_ReachedTarget)
    {
        GoToBestTarget(deltaTime);
    }
    else
    {
        ShowNavigationPath();
    }*/

	if (!m_ReachedTarget) {
		ShowNavigationPath();
	}
}

void ASDTBaseAIController::StartBehaviorTree(APawn* pawn)
{
	if (ASoftDesignTrainingCharacter* aiBaseCharacter = Cast<ASoftDesignTrainingCharacter>(pawn))
	{
		if (aiBaseCharacter->GetBehaviorTree())
		{
			m_behaviorTreeComponent->StartTree(*aiBaseCharacter->GetBehaviorTree());
		}
	}
}

void ASDTBaseAIController::StopBehaviorTree(APawn* pawn)
{
	if (ASoftDesignTrainingCharacter* aiBaseCharacter = Cast<ASoftDesignTrainingCharacter>(pawn))
	{
		if (aiBaseCharacter->GetBehaviorTree())
		{
			m_behaviorTreeComponent->StopTree();
		}
	}
}

void ASDTBaseAIController::Possess(APawn* pawn)
{
	Super::Possess(pawn);

	if (ASoftDesignTrainingCharacter* aiBaseCharacter = Cast<ASoftDesignTrainingCharacter>(pawn))
	{
		if (aiBaseCharacter->GetBehaviorTree())
		{
			m_blackboardComponent->InitializeBlackboard(*aiBaseCharacter->GetBehaviorTree()->BlackboardAsset);

			m_reachedTargetBBKeyID = m_blackboardComponent->GetKeyID("ReachedTarget");

			//Set this agent in the BT
			m_blackboardComponent->SetValue<UBlackboardKeyType_Object>(m_blackboardComponent->GetKeyID("SelfActor"), pawn);
		}
	}
}


