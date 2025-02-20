// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
#include "SoftDesignTrainingMainCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "SDTAIController.h"
#include "SDTProjectile.h"
#include "SDTUtils.h"
#include "DrawDebugHelpers.h"
#include "SDTCollectible.h"
#include "SDTBaseAIController.h"


ASoftDesignTrainingCharacter::ASoftDesignTrainingCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
}

void ASoftDesignTrainingCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASoftDesignTrainingCharacter::OnBeginOverlap);
    m_StartingPosition = GetActorLocation();

	// BT_AI
	if (ASDTBaseAIController* aiController = Cast<ASDTBaseAIController>(GetController()))
	{
		aiController->GetBlackBoardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetReachedTargetKeyID(), true);
		aiController->GetBlackBoardComponent()->SetValue<UBlackboardKeyType_Bool>(aiController->GetLostPlayerSightKeyID(), true);
		aiController->StartBehaviorTree(this);
	}
}

void ASoftDesignTrainingCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherComponent->GetCollisionObjectType() == COLLISION_DEATH_OBJECT)
    {
        Die();
    }
    else if(ASDTCollectible* collectibleActor = Cast<ASDTCollectible>(OtherActor))
    {
        if (!collectibleActor->IsOnCooldown())
        {
            OnCollectPowerUp();
        }

        collectibleActor->Collect();
    }
    else if (ASoftDesignTrainingMainCharacter* mainCharacter = Cast<ASoftDesignTrainingMainCharacter>(OtherActor))
    {
        if (mainCharacter->IsPoweredUp())
            Die();
    }
}

void ASoftDesignTrainingCharacter::Die()
{
    SetActorLocation(m_StartingPosition);

    if (ASDTAIController* controller = Cast<ASDTAIController>(GetController()))
    {
        controller->AIStateInterrupted();
    }
}
