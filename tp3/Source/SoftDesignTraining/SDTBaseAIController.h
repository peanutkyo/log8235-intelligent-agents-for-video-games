// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "SDTBaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API ASDTBaseAIController : public AAIController
{
	GENERATED_BODY()

public:

    ASDTBaseAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
    virtual void Tick(float deltaTime) override;

	// BT_AI
	UBehaviorTreeComponent* GetBehaviorTreeComponent() const { return m_behaviorTreeComponent; }
	UBlackboardComponent*   GetBlackBoardComponent() const { return m_blackboardComponent; }

	uint8                   GetReachedTargetKeyID() const { return m_reachedTargetBBKeyID; }

	void                    StartBehaviorTree(APawn* pawn);
	void                    StopBehaviorTree(APawn* pawn);
	
protected:
    virtual void RotationUpdate(float deltaTime) {};
    virtual void ImpulseToDirection(float deltaTime) {};

    bool m_ReachedTarget;

	// BT_AI
	virtual void Possess(APawn* pawn) override;

private:
    virtual void GoToBestTarget(float deltaTime) {};
    virtual void UpdatePlayerInteraction(float deltaTime) {};
    virtual void ShowNavigationPath() {};

	// BT_AI
	UPROPERTY(transient)
		UBehaviorTreeComponent* m_behaviorTreeComponent;

	UPROPERTY(transient)
		UBlackboardComponent* m_blackboardComponent;


	uint8   m_reachedTargetBBKeyID;
};
