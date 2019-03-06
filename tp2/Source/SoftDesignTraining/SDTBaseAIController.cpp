// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SDTBaseAIController.h"
#include <Engine/Engine.h>


ASDTBaseAIController::ASDTBaseAIController(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    m_ReachedTarget = true;
}

void ASDTBaseAIController::BeginPlay() {
	Super::BeginPlay();

	m_PathFollowingComponent = Cast<USDTPathFollowingComponent>(GetComponentByClass(USDTPathFollowingComponent::StaticClass()));
}

void ASDTBaseAIController::Tick(float deltaTime)
{
    Super::Tick(deltaTime);

    ChooseBehavior(deltaTime);

    if (m_ReachedTarget)
    {
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, TEXT("GoToBestTarget"));
        GoToBestTarget(deltaTime);
    }
    else
    {
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Green, TEXT("ShowNavigationPath"));
        ShowNavigationPath();
    }
}


