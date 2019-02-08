// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SDTAIController.h"
#include "DrawDebugHelpers.h"
#include "PhysicsHelpers.h"
#include "SDTCollectible.h"
#include "Engine.h"
#include <random>

void ASDTAIController::Tick(float deltaTime)
{
	UWorld* world = GetWorld();
	APawn* pawn = GetPawn();
	PhysicsHelpers physicsHelper = PhysicsHelpers(world);

	//DrawVisionCone(world, pawn, pawn->GetActorForwardVector(), m_visionAngle);
	TArray<FOverlapResult> detectedItems = CollectTargetActorsInFrontOfCharacter(pawn, physicsHelper);

	target = nullptr;
	for (FOverlapResult item : detectedItems)
	{
		/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, FString(item.GetActor()->FindComponentByClass<UPrimitiveComponent>()->GetCollisionProfileName().ToString()));*/

		if (item.GetActor()->IsA(ASDTCollectible::StaticClass()))
		{
			FVector2D collectible = FVector2D(item.GetActor()->GetActorLocation());
			if (Cast<ASDTCollectible>(item.GetActor())->GetStaticMeshComponent()->IsVisible() && CheckTargetVisibility(item.GetActor(), physicsHelper)) {
				target = item.GetActor();
				MoveToTarget(collectible, m_maxSpeed, deltaTime);
			}
			break;
		}
		else if (item.GetActor()->FindComponentByClass<UPrimitiveComponent>()->GetCollisionProfileName().ToString() == "DeathObject") {
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, FString("Death Floor Detected!!!"));
		}
	}

	if (GEngine)
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, FString(target == nullptr ? "no target focused" : "target in field of view"));

	if (target == nullptr) {
		//MoveTowardsDirection(FVector2D(pawn->GetActorForwardVector()), m_maxSpeed, deltaTime);
		NavigateAround(world, pawn, deltaTime);
	}

	DisplayMetrics(deltaTime);
}

void ASDTAIController::MoveForward(APawn* pawn, float acceleration, float maxSpeed) 
{
	pawn->AddMovementInput(pawn->GetActorForwardVector(), m_currentSpeed, true);
}

float ASDTAIController::IncreaseSpeed(float acceleration, float maxSpeed, float deltaTime) 
{
	float newSpeed = m_currentSpeed + acceleration * deltaTime;

	newSpeed = FMath::Clamp(newSpeed, 0.1f, maxSpeed);
	return newSpeed;
}

void ASDTAIController::RotateToDirection(APawn* pawn, FVector direction, float deltaTime)
{
	//FVector forwardVector = pawn->GetActorForwardVector();
	//FVector dir = (direction - forwardVector);
	direction.Normalize();
	//dir.Normalize();
	//pawn->AddActorWorldRotation(FMath::Lerp(forwardVector.ToOrientationRotator(), dir.ToOrientationRotator(), 0.05f));

	// TODO: Gradual rotation ?
	pawn->AddActorWorldRotation(direction.ToOrientationRotator()); // this line does a snap rotation (ugly)
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

void ASDTAIController::MoveTowardsDirection(FVector2D direction, float speed, float deltaTime)
{
	APawn* pawn = GetPawn();
	FVector const pawnPosition(pawn->GetActorLocation());
	FVector2D const displacement = FMath::Min(m_maxSpeed, speed) * deltaTime * direction.GetSafeNormal();
	
	pawn->SetActorLocation(pawnPosition + FVector(displacement, 0.f), true);
	pawn->SetActorRotation(FVector(direction, 0.f).ToOrientationQuat());
}

void ASDTAIController::DrawVisionCone(UWorld* world, APawn* pawn, FVector const& dir, float angle) const
{
	DrawDebugCone(world, pawn->GetActorLocation(), dir, 5000.0f, angle, angle, 50, FColor::Green, false, -1.0f, 0, 5.0f);
}

TArray<FOverlapResult> ASDTAIController::CollectTargetActorsInFrontOfCharacter(APawn const* pawn, PhysicsHelpers& physicHelper) const
{
	TArray<FOverlapResult> outResults;
	physicHelper.SphereOverlap(pawn->GetActorLocation() + pawn->GetActorForwardVector() * m_visionRadius, m_visionRadius, outResults, false);
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
	bool detected = physicHelper.SphereCast(pawn->GetActorLocation(), target->GetActorLocation(), 42, outHitResults, true);
	if (GEngine && detected)
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, FString(outHitResults[0].GetActor()->GetName()));
	if (detected) {
		return false;
	}
	return true;
}

void ASDTAIController::DisplayMetrics(float deltaTime)
{
	if (m_enableMetrics && GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::Printf(TEXT("--------------------------------------------------------")));
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
	// should be a serializefield kinda
	const float distanceToObstacle = 200.f; // 200.f worked the best
	const float maxSpeed = 1.f;
	const float acceleration = 0.1f;
	const float slowDownFactor = -5.f; // -5.f worked best for slowing down before turning

									   // We start by raycasting around us.
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	FHitResult losHit;
	FCollisionQueryParams queryParams = FCollisionQueryParams();
	queryParams.AddIgnoredActor(pawn);
	bool isGonnaCollideForward = world->LineTraceSingleByObjectType
	(
		losHit,
		pawn->GetActorLocation(),
		pawn->GetActorLocation() + distanceToObstacle * pawn->GetActorForwardVector(),
		TraceObjectTypes, queryParams
	);
	bool isGonnaCollideBehind = world->LineTraceSingleByObjectType
	(
		losHit,
		pawn->GetActorLocation(),
		pawn->GetActorLocation() + distanceToObstacle * -1.0f *  pawn->GetActorForwardVector(),
		TraceObjectTypes, queryParams
	);
	bool isGonnaCollideRight = world->LineTraceSingleByObjectType
	(
		losHit,
		pawn->GetActorLocation(),
		pawn->GetActorLocation() + distanceToObstacle * pawn->GetActorRightVector(),
		TraceObjectTypes, queryParams
	);

	bool isGonnaCollideLeft = world->LineTraceSingleByObjectType
	(
		losHit,
		pawn->GetActorLocation(),
		pawn->GetActorLocation() + distanceToObstacle * -1.0f * pawn->GetActorRightVector(),
		TraceObjectTypes, queryParams
	);

	bool isTurning = false;

	// Random generator lets us sometimes choose a different direction if it's possible
	// Source: https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, 1);
	// If there's a wall ahead...
	if (!isGonnaCollideForward)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No collision forward."));
		UE_LOG(LogTemp, Warning, TEXT("No collision forward."));
		m_currentSpeed = IncreaseSpeed(acceleration, maxSpeed, deltaTime);
		MoveForward(pawn, acceleration, maxSpeed);
	}
	else if (!isGonnaCollideLeft && distr(eng))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No collision left."));
		UE_LOG(LogTemp, Warning, TEXT("No collision left."));

		// turn 45 degrees
		FVector newDirection = -1.0f * FVector(1.f, 1.f, 0.f); // to the left
		if (!pawn->GetActorForwardVector().Equals(newDirection, 0.1f))
		{
			isTurning = true;
		}
		if (isTurning)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Engaging drift procedure to the left."));
			UE_LOG(LogTemp, Warning, TEXT("Engaging drift procedure to the left."));
			RotateToDirection(pawn, newDirection, deltaTime);
			m_currentSpeed = IncreaseSpeed(slowDownFactor * acceleration, maxSpeed, deltaTime);
		}
	}
	else if (!isGonnaCollideRight && distr(eng))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No collision right."));
		UE_LOG(LogTemp, Warning, TEXT("No collision right."));

		// turn 45 degrees
		FVector newDirection = FVector(1.f, 1.f, 0.f);
		if (!pawn->GetActorForwardVector().Equals(newDirection, 0.1f))
		{
			isTurning = true;
		}
		if (isTurning)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Engaging drift procedure to the right."));
			UE_LOG(LogTemp, Warning, TEXT("Engaging drift procedure to the right."));
			RotateToDirection(pawn, newDirection, deltaTime);
			m_currentSpeed = IncreaseSpeed(slowDownFactor * acceleration, maxSpeed, deltaTime);
		}
	}
	else if (!isGonnaCollideBehind)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No collision behind."));
		UE_LOG(LogTemp, Warning, TEXT("No collision behind."));

		// turn 45 degrees
		FVector newDirection = -1.f * pawn->GetActorForwardVector();
		if (!pawn->GetActorForwardVector().Equals(newDirection, 0.1f))
		{
			isTurning = true;
		}
		if (isTurning)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Engaging drift procedure behind."));
			UE_LOG(LogTemp, Warning, TEXT("Engaging drift procedure behind."));
			RotateToDirection(pawn, newDirection, deltaTime);
			m_currentSpeed = IncreaseSpeed(slowDownFactor * acceleration, maxSpeed, deltaTime);
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("AI is stuck. We reset his position."));
		UE_LOG(LogTemp, Warning, TEXT("AI is stuck. We reset his position."));
		// turn 45 degrees
		FVector newDirection = FVector(1.f, 1.f, 0.f);
		if (!pawn->GetActorForwardVector().Equals(newDirection, 0.1f))
		{
			isTurning = true;
		}
		if (isTurning)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Engaging drift procedure to the right."));
			UE_LOG(LogTemp, Warning, TEXT("Engaging drift procedure to the right."));
			RotateToDirection(pawn, newDirection, deltaTime);
			m_currentSpeed = IncreaseSpeed(slowDownFactor * acceleration, maxSpeed, deltaTime);
		}
	}
}
