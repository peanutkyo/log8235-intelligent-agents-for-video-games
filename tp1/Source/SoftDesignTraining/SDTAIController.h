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
	void MoveToOppositeDirectionOfTarget(FVector2D target, float targetSpeed, float deltaTime);
	void MoveTowardsDirection(FVector2D direction, float speed, float deltaTime);
	void NavigateAround(UWorld* world, APawn* pawn, float deltaTime);

	TArray<FOverlapResult> CollectTargetActorsInFrontOfCharacter(APawn const* pawn, PhysicsHelpers& physicHelper) const;

	void MoveForward(APawn* pawn);
	float IncreaseSpeed(float acceleration, float maxSpeed, float deltaTime);
	bool RotateToDirection(APawn* pawn, FVector direction, float deltaTime);
	void TurnToDirection(APawn* pawn, float deltaTime);

	bool CheckTargetVisibility(AActor* target, PhysicsHelpers& physicHelper);
	void DisplayMetrics(float deltaTime);

	/* Indique la vitesse maximale que le personnage AI est capable de bouger. */
	UPROPERTY(EditAnywhere)
		float m_maxSpeed = 100.0f;

	/* Indique la vitesse actuelle du personnage. C'est aussi sa vitesse de depart avant de partir le jeu. */
	UPROPERTY(EditAnywhere)
		float m_currentSpeed = 0.5f;

	/* Indique l'acc�l�ration du personnage AI. Elle vient modifier la vitesse actuelle du personnage. */
	UPROPERTY(EditAnywhere)
		float m_acceleration = 1.0f;

	/* Indique le rayon maximal de la sphere de vision dont le personnage AI est capable de voir. */
	UPROPERTY(EditAnywhere)
		float m_visionRadius = 500.0f;

	/* Indique la distance minimale avant de detecter une collision */
	UPROPERTY(EditAnywhere)
		float m_distanceToObstacle = 200.0f;

	/* Indique le facteur de modification pour decelerer lors de virages */
	UPROPERTY(EditAnywhere)
		float m_slowDownFactor = -5.0f;

	/* Indique si on veut afficher les donnees metriques du jeu pour l'analyse. */
	UPROPERTY(EditAnywhere)
		bool m_enableMetrics = true;

	/* Indique la p�riode de temps en secondes dans laquelle on recueille des donnees avant de r�initialiser. */
	UPROPERTY(EditAnywhere)
		float m_metricsPeriod = 60;

	/* Indique si les options de debug sont actives ou pas. */
	UPROPERTY(EditAnywhere)
		bool m_enableDebug = false;

	int m_nPickup = 0;
	int m_nDeath = 0;
	float m_currentLiveTime = 0.f;
	int m_nPeriod = 1;

	AActor* target = nullptr;

	enum struct SDTAI_State { PURSUIT, FLEE };
	SDTAI_State m_currentState = SDTAI_State::PURSUIT;

	bool m_isChangingDirection = false;
	FVector m_newDirection = FVector(0.f, 0.f, 0.f);
};
