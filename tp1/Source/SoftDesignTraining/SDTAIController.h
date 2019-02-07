// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "SDTAIController.generated.h"


class PhysicsHelpers;

/**
 * 
 */
UCLASS(ClassGroup = AI, config = Game)
class SOFTDESIGNTRAINING_API ASDTAIController : public AAIController
{
    GENERATED_BODY()
public:
    virtual void Tick(float deltaTime) override;

protected:
	virtual bool MoveToTarget(FVector2D target, float speed, float deltaTime);
	virtual void MoveTowardsDirection(FVector2D direction, float speed, float deltaTime);

	virtual void DrawVisionCone(UWorld* world, APawn* pawn, FVector const& dir, float angle) const;
	virtual TArray<FOverlapResult> CollectTargetActorsInFrontOfCharacter(APawn const* pawn, PhysicsHelpers& physicHelper) const;

	virtual void ASDTAIController::MoveForward(APawn* pawn, float acceleration, float maxSpeed);
	virtual float ASDTAIController::IncreaseSpeed(float acceleration, float maxSpeed, float deltaTime);
	virtual void ASDTAIController::RotateToDirection(APawn* pawn, FVector direction, float deltaTime);


	FVector2D m_MovementInput;
	float const m_maxSpeed = 500.0f;
	float const m_visionAngle = PI / 3.0f;
	float m_currentSpeed = 0.5f;

	enum struct SDTAI_State { PURSUIT, FLEE };
	SDTAI_State m_currentState = SDTAI_State::PURSUIT;
};
