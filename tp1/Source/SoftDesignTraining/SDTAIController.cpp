// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "DrawDebugHelpers.h"
#include "PhysicsHelpers.h"
#include "SDTCollectible.h"
#include "SoftDesignTrainingMainCharacter.h"
#include "Engine.h"
#include <random>

void ASDTAIController::Tick(float deltaTime)
{
	UWorld* world = GetWorld();
	APawn* pawn = GetPawn();
	PhysicsHelpers physicsHelper = PhysicsHelpers(world);

	TArray<FOverlapResult> detectedItems = CollectTargetActorsInFrontOfCharacter(pawn, physicsHelper);

	if (m_currentState == SDTAI_State::FLEE && target != nullptr && target->IsA(ASoftDesignTrainingMainCharacter::StaticClass())) {
		if (CheckTargetVisibility(target, physicsHelper)) {
			MoveToOppositeDirectionOfTarget(FVector2D(target->GetActorLocation()), m_maxSpeed, deltaTime);
		}
		else {
			target = nullptr;
		}
	}
	else {

		// Find the target of upmost priority
		target = nullptr;
		int priority = 0;
		for (FOverlapResult item : detectedItems)
		{
			AActor* itemActor = item.GetActor();
			if (priority < 2 && itemActor->IsA(ASoftDesignTrainingMainCharacter::StaticClass())) {
				if (CheckTargetVisibility(itemActor, physicsHelper)) {
					target = itemActor;
					priority = 2;
					break;
				}
			}
			else if (priority < 1 && itemActor->IsA(ASDTCollectible::StaticClass())) {
				if (Cast<ASDTCollectible>(itemActor)->GetStaticMeshComponent()->IsVisible() && CheckTargetVisibility(itemActor, physicsHelper)) {
					target = itemActor;
					priority = 1;
				}
			}
		}

		// if no target is found, randomly choose walk around
		if (target == nullptr) {
			NavigateAround(world, pawn, deltaTime);
		}
		else {
			// Make decision based on target object type
			if (target->IsA(ASDTCollectible::StaticClass()))
			{
				FVector2D collectible = FVector2D(target->GetActorLocation());
				MoveToTarget(collectible, m_maxSpeed, deltaTime);
			}
			else if (target->IsA(ASoftDesignTrainingMainCharacter::StaticClass())) {
				if (Cast<ASoftDesignTrainingMainCharacter>(target)->IsPoweredUp()) {
					m_currentState = SDTAI_State::FLEE;
				}
				else {
					m_currentState = SDTAI_State::PURSUIT;
					FVector2D player = FVector2D(target->GetActorLocation());
					MoveToTarget(player, m_maxSpeed, deltaTime);
				}
			}
		}
	}

	DisplayMetrics(deltaTime);
}

void ASDTAIController::MoveForward(APawn* pawn) 
{
	pawn->AddMovementInput(pawn->GetActorForwardVector(), m_currentSpeed, true);
}

float ASDTAIController::IncreaseSpeed(float acceleration, float maxSpeed, float deltaTime) 
{
	float newSpeed = m_currentSpeed + acceleration * deltaTime;

	newSpeed = FMath::Clamp(newSpeed, 0.1f, maxSpeed);
	return newSpeed;
}

bool ASDTAIController::RotateToDirection(APawn* pawn, FVector direction, float deltaTime)
{
	direction.Normalize();
	FVector forwardVector = pawn->GetActorForwardVector();
	FVector newDir = (direction - forwardVector);
	newDir.Normalize();
	pawn->SetActorRotation(FMath::Lerp(forwardVector.ToOrientationRotator(), newDir.ToOrientationRotator(), 0.05f));

	return (forwardVector.Equals(direction, 0.6f));
}

bool ASDTAIController::MoveToTarget(FVector2D target, float targetSpeed, float deltaTime)
{
	APawn* pawn = GetPawn();
	FVector const pawnPosition(pawn->GetActorLocation());
	FVector2D const toTarget = target - FVector2D(pawnPosition);
	FVector2D const displacement = FMath::Min(toTarget.Size(), FMath::Min(m_maxSpeed, targetSpeed) * deltaTime) * toTarget.GetSafeNormal();
	pawn->AddMovementInput(FVector(displacement, 0.f), m_currentSpeed, true);
	//pawn->SetActorLocation(pawnPosition + FVector(displacement, 0.f), true);
	pawn->SetActorRotation(FVector(displacement, 0.f).ToOrientationQuat());
	return toTarget.Size() < FMath::Min(m_maxSpeed, targetSpeed) * deltaTime;
}

void ASDTAIController::MoveToOppositeDirectionOfTarget(FVector2D target, float targetSpeed, float deltaTime) {
	APawn* pawn = GetPawn();
	FVector const pawnPosition(pawn->GetActorLocation());
	FVector2D const toTarget = -1 * (target - FVector2D(pawnPosition));
	FVector2D const displacement = FMath::Min(toTarget.Size(), FMath::Min(m_maxSpeed, targetSpeed) * deltaTime) * toTarget.GetSafeNormal();
	pawn->AddMovementInput(FVector(displacement, 0.f), m_currentSpeed, true);
	//pawn->SetActorLocation(pawnPosition + FVector(displacement, 0.f), true);
	pawn->SetActorRotation(FVector(displacement, 0.f).ToOrientationQuat());
}

void ASDTAIController::MoveTowardsDirection(FVector2D direction, float speed, float deltaTime)
{
	APawn* pawn = GetPawn();
	FVector const pawnPosition(pawn->GetActorLocation());
	FVector2D const displacement = FMath::Min(m_maxSpeed, speed) * deltaTime * direction.GetSafeNormal();
	
	pawn->SetActorLocation(pawnPosition + FVector(displacement, 0.f), true);
	pawn->SetActorRotation(FVector(direction, 0.f).ToOrientationQuat());
}

TArray<FOverlapResult> ASDTAIController::CollectTargetActorsInFrontOfCharacter(APawn const* pawn, PhysicsHelpers& physicHelper) const
{
	TArray<FOverlapResult> outResults;
	physicHelper.SphereOverlap(pawn->GetActorLocation() + pawn->GetActorForwardVector() * m_visionRadius, m_visionRadius, outResults, m_enableDebug);
	return outResults;
}

void ASDTAIController::AddCollectedCount()
{
	m_nPickup++;
}

void ASDTAIController::AddDeathCount()
{
	m_nDeath++;
}

bool ASDTAIController::CheckTargetVisibility(AActor * target, PhysicsHelpers& physicHelper)
{
	APawn* pawn = GetPawn();
	TArray<FHitResult> outHitResults;
	bool detected = physicHelper.SphereCast(pawn->GetActorLocation(), target->GetActorLocation(), 42, outHitResults, m_enableDebug);
	if (detected && outHitResults[0].GetActor()->IsA(target->GetClass())) {
		return true;
	}
	return false;
}

void ASDTAIController::DisplayMetrics(float deltaTime)
{
	if (m_enableMetrics && GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::Printf(TEXT("--------------------------------------------------------")));
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::Printf(TEXT("Etat courant : en %s"), *FString(m_currentState == SDTAI_State::PURSUIT ? "poursuite" : "fuite")));
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::Printf(TEXT("Cible courant : %s"), *FString(target == nullptr ? "aucun cible en focus" : target->GetName())));
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::Printf(TEXT("Nombre de mort du AI : %s"), *FString::FromInt(m_nDeath)));
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::Printf(TEXT("Nombre de Pickup ramasse par AI : %s"), *FString::FromInt(m_nPickup)));

		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::Printf(TEXT("Temps de periode ecoule : %s secondes"), *FString::SanitizeFloat(m_currentLiveTime)));
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::Printf(TEXT("Periode no. %s"), *FString::FromInt(m_nPeriod)));
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::Printf(TEXT("------------- %s -------------"), *(GetPawn()->GetName())));

		m_currentLiveTime += deltaTime;
		if (m_currentLiveTime >= m_metricsPeriod) {
			m_nPickup = 0;
			m_nDeath = 0;

			m_currentLiveTime = 0;
			m_nPeriod++;
		}
	}
}

void ASDTAIController::NavigateAround(UWorld* world, APawn* pawn, float deltaTime) {
	// We start by raycasting around us.
	FCollisionObjectQueryParams objectQueryParamsWall;
	objectQueryParamsWall.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	FHitResult losHit;
	FCollisionQueryParams queryParams = FCollisionQueryParams();
	queryParams.AddIgnoredActor(pawn);

	bool isGonnaCollideForward = world->LineTraceSingleByObjectType
	(
		losHit,
		pawn->GetActorLocation(),
		pawn->GetActorLocation() + m_distanceToObstacle * pawn->GetActorForwardVector(),
		objectQueryParamsWall, queryParams
	);

	// Calculate raycast vector for death floors
	FVector floorLevel = FVector(0.f, 0.f, -100.f);
	FVector deathFloorVector = pawn->GetActorLocation() + m_distanceToObstacle / 2 * pawn->GetActorForwardVector() + floorLevel;

	if (m_enableDebug)
		DrawDebugLine(world, pawn->GetActorLocation(), deathFloorVector, FColor::Magenta);

	FCollisionObjectQueryParams objectQueryParamsDeathFloor;
	objectQueryParamsDeathFloor.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel3);
	bool isGonnaHitDeathFloorForward = world->LineTraceSingleByObjectType
	(
		losHit,
		pawn->GetActorLocation(),
		deathFloorVector,
		objectQueryParamsDeathFloor, queryParams
	);

	bool isGonnaCollideBehind = world->LineTraceSingleByObjectType
	(
		losHit,
		pawn->GetActorLocation(),
		pawn->GetActorLocation() + m_distanceToObstacle * -1.0f *  pawn->GetActorForwardVector(),
		objectQueryParamsWall, queryParams
	);
	bool isGonnaCollideRight = world->LineTraceSingleByObjectType
	(
		losHit,
		pawn->GetActorLocation(),
		pawn->GetActorLocation() + m_distanceToObstacle * pawn->GetActorRightVector(),
		objectQueryParamsWall, queryParams
	);

	bool isGonnaCollideLeft = world->LineTraceSingleByObjectType
	(
		losHit,
		pawn->GetActorLocation(),
		pawn->GetActorLocation() + m_distanceToObstacle * -1.0f * pawn->GetActorRightVector(),
		objectQueryParamsWall, queryParams
	);

	// Random generator lets us sometimes choose a different direction if it's possible
	// Source: https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, 1);
	// If there's a wall ahead...
	if (!m_isChangingDirection) {
		if (!isGonnaCollideForward && !isGonnaHitDeathFloorForward)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No collision forward."));
			//UE_LOG(LogTemp, Warning, TEXT("No collision forward."));
			m_currentSpeed = IncreaseSpeed(m_acceleration, m_maxSpeed, deltaTime);
			MoveForward(pawn);
		}
		else if (!isGonnaCollideLeft && distr(eng))
		{
			m_isChangingDirection = true;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No collision left."));
			//UE_LOG(LogTemp, Warning, TEXT("No collision left."));

			m_newDirection = -1.0f * FVector(1.f, 1.f, 0.f); // to the left
			m_newDirection.Normalize();

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Engaging drift procedure to the left."));
			//UE_LOG(LogTemp, Warning, TEXT("Engaging drift procedure to the left."));
			m_currentSpeed = IncreaseSpeed(m_slowDownFactor * m_acceleration, m_maxSpeed, deltaTime);
			TurnToDirection(pawn, deltaTime);
		}
		else if (!isGonnaCollideRight && distr(eng))
		{
			m_isChangingDirection = true;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No collision right."));
			//UE_LOG(LogTemp, Warning, TEXT("No collision right."));

			m_newDirection = FVector(1.f, 1.f, 0.f);
			m_newDirection.Normalize();

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Engaging drift procedure to the right."));
			//UE_LOG(LogTemp, Warning, TEXT("Engaging drift procedure to the right."));
			m_currentSpeed = IncreaseSpeed(m_slowDownFactor * m_acceleration, m_maxSpeed, deltaTime);
			TurnToDirection(pawn, deltaTime);
		}
		else if (!isGonnaCollideBehind)
		{
			m_isChangingDirection = true;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No collision behind."));
			//UE_LOG(LogTemp, Warning, TEXT("No collision behind."));

			m_newDirection = -1.f * pawn->GetActorForwardVector();

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Engaging drift procedure behind."));
			//UE_LOG(LogTemp, Warning, TEXT("Engaging drift procedure behind."));
			m_currentSpeed = IncreaseSpeed(m_slowDownFactor * m_acceleration, m_maxSpeed, deltaTime);
			TurnToDirection(pawn, deltaTime);
		}
		else
		{
			m_isChangingDirection = true;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("AI is stuck. We reset his position."));
			//UE_LOG(LogTemp, Warning, TEXT("AI is stuck. We reset his position."));

			m_newDirection = FVector(0.5f, 1.f, 0.f);
			m_newDirection.Normalize();

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Engaging drift procedure to the right."));
			//UE_LOG(LogTemp, Warning, TEXT("Engaging drift procedure to the right."));
			m_currentSpeed = IncreaseSpeed(m_slowDownFactor * m_acceleration, m_maxSpeed, deltaTime);
			TurnToDirection(pawn, deltaTime);
		}
	}
	else {
		TurnToDirection(pawn, deltaTime);
	}
}

void ASDTAIController::TurnToDirection(APawn* pawn, float deltaTime) {
	if (RotateToDirection(pawn, m_newDirection, deltaTime)) {
		m_isChangingDirection = false;
		UE_LOG(LogTemp, Warning, TEXT("Finished rotating."));
	}
}
