#include "SoftDesignTraining.h"
#include "AiGroupManager.h"
#include <cmath>


AiGroupManager::AiGroupManager()
{
}

void AiGroupManager::ClearChasePoints()
{
	m_chasePoints.Empty();
}

void AiGroupManager::UpdateChasePoints()
{
	for (int i = 0; i < m_aiActors.Num(); i++) {
		float currentAngle = (i * 360.f) / m_aiActors.Num();
		float x = m_radius * cos(currentAngle);
		float z = m_radius * sin(currentAngle);
		FVector chasePoint = m_target->GetTargetLocation();
		FVector offset = FVector(x, chasePoint.Y, z);

		chasePoint += offset;
		m_chasePoints.Add(chasePoint);
	}
}

void AiGroupManager::AddAIActorToGroup(ASDTAIController* aiActor)
{
	m_aiActors.Add(aiActor);
	ClearChasePoints();
	UpdateChasePoints();
}

void AiGroupManager::RemoveAIActorFromGroup(ASDTAIController* aiActor)
{
	m_aiActors.Remove(aiActor);
}

void AiGroupManager::AssignChasePointsToAiActors()
{
	for (int i = 0; i < m_aiActors.Num(); i++) {
		m_aiActors[i]->MoveTo(m_chasePoints[i]);
	}
}

