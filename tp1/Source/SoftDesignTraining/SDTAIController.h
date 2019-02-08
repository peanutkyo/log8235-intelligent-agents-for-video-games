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
	void AddCollectedCount();
	void AddDeathCount();

private:
	bool MoveToTarget(FVector2D target, float speed, float deltaTime);
	void MoveTowardsDirection(FVector2D direction, float speed, float deltaTime);
	void NavigateAround(UWorld* world, APawn* pawn, float deltaTime);

	void DrawVisionCone(UWorld* world, APawn* pawn, FVector const& dir, float angle) const;
	TArray<FOverlapResult> CollectTargetActorsInFrontOfCharacter(APawn const* pawn, PhysicsHelpers& physicHelper) const;

	void MoveForward(APawn* pawn, float acceleration, float maxSpeed);
	float IncreaseSpeed(float acceleration, float maxSpeed, float deltaTime);
	void RotateToDirection(APawn* pawn, FVector direction, float deltaTime);

	bool CheckTargetVisibility(AActor* target, PhysicsHelpers& physicHelper);
	void DisplayMetrics(float deltaTime);

	/** Indique la vitesse maximale que le personnage AI est capable de bouger, donc il devrait pouvoir acc�l�rer jusqu'� atteindre cette vitesse maximale. */
	UPROPERTY(EditAnywhere)
		float m_maxSpeed = 100.0f;

	/** Indique l'acc�l�ration du changement de vitesse du personnage AI, cela est aussi valable en tant qu'acc�l�ration que d�c�l�ration. */
	UPROPERTY(EditAnywhere)
		float m_acceleration = 1.0f;

	/** Indique le rayon maximal du sphere de vision dont le personnage AI est capable de voir. */
	UPROPERTY(EditAnywhere)
		float m_visionRadius = 500.0f;

	/** Indique si on veut afficher les donnees metriques du jeu pour l'analyse. */
	UPROPERTY(EditAnywhere)
		bool m_enableMetrics = true;

	/** Indique si la p�riode de temps en seconde dans laquelle on recueille des donnees avant de r�initialiser. */
	UPROPERTY(EditAnywhere)
		float m_metricsPeriod = 60;

	int m_nPickup = 0;
	int m_nDeath = 0;
	float m_currentLiveTime = 0.f;
	int m_nPeriod = 1;

	AActor* target = nullptr;

	float m_currentSpeed = 0.5f;

	enum struct SDTAI_State { PURSUIT, FLEE };
	SDTAI_State m_currentState = SDTAI_State::PURSUIT;
};
