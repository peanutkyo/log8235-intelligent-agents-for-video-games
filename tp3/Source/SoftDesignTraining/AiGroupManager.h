// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SDTBaseAIController.h"
#include "GameFramework/Actor.h"
#include "AiGroupManager.generated.h"

UCLASS()
class SOFTDESIGNTRAINING_API AAiGroupManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AAiGroupManager();
	void ClearChasePoints();
	void UpdateChasePoints();
	void AddAIActorToGroup(ASDTBaseAIController* aiActor);
	void RemoveAIActorFromGroup(ASDTBaseAIController* aiActor);
	void DrawChasePoints();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void AssignChasePointsToAiActors();

	float m_radius = 250;
	ACharacter* m_target;
	TArray<ASDTBaseAIController*> m_aiActors;
	TArray<FVector> m_chasePoints;
	
};
