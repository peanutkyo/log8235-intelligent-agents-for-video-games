#pragma once

#include "CoreMinimal.h"
#include "SDTAIController.h"


class SOFTDESIGNTRAINING_API AiGroupManager
{

public:
	AiGroupManager();
	void ClearChasePoints();
	void UpdateChasePoints();
	void AddAIActorToGroup(ASDTAIController* aiActor);
	void RemoveAIActorFromGroup(ASDTAIController* aiActor);

private:
	void AssignChasePointsToAiActors();

	float m_radius = 500.f;
	ACharacter* m_target;
	TArray<ASDTAIController*> m_aiActors;
	TArray<FVector> m_chasePoints;
};
