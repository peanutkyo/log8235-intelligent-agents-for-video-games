#include "SoftDesignTraining.h"
#include "AiGroupManager.h"
#include "DrawDebugHelpers.h"
#include <cmath>
#include "Engine.h"


AAiGroupManager::AAiGroupManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAiGroupManager::BeginPlay()
{
	Super::BeginPlay();

	m_target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void AAiGroupManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawChasePoints();
}

void AAiGroupManager::ClearChasePoints()
{
	m_chasePoints.Empty();
}

void AAiGroupManager::UpdateChasePoints()
{
	FVector chasePoint = m_target->GetActorLocation();
	if (m_aiActors.Num() == 1) {
		m_chasePoints.Add(FVector(0, 0, 0));
	}
	else {
		for (int i = 0; i < m_aiActors.Num(); i++) {
			float currentAngle = (i * 2 * PI) / m_aiActors.Num();
			float x = m_radius * cos(currentAngle);
			float y = m_radius * sin(currentAngle);
			FVector offset = FVector(x, y, 0);

			//chasePoint += offset;
			m_chasePoints.Add(offset);
		}
	}
}

void AAiGroupManager::AddAIActorToGroup(ASDTBaseAIController* aiActor)
{
	m_aiActors.Add(aiActor);
	ClearChasePoints();
	UpdateChasePoints();
	AssignChasePointsToAiActors();
}

void AAiGroupManager::RemoveAIActorFromGroup(ASDTBaseAIController* aiActor)
{
	m_aiActors.Remove(aiActor);
	ClearChasePoints();
	UpdateChasePoints();
	AssignChasePointsToAiActors();
}

void AAiGroupManager::AssignChasePointsToAiActors()
{
	for (int i = 0; i < m_aiActors.Num(); i++) {
		m_aiActors[i]->SetChasePoint(m_chasePoints[i]);
	}
}

void AAiGroupManager::DrawChasePoints()
{
	for (int i = 0; i < m_chasePoints.Num(); i++)
	{
		DrawDebugSphere(GetWorld(), m_target->GetActorLocation() + m_chasePoints[i], 15.0f, 100, FColor::Red);
	}
}

