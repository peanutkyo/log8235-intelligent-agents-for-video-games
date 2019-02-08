// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"

#include "SDTCollectible.generated.h"

/**
*
*/
UCLASS()
class SOFTDESIGNTRAINING_API ASDTCollectible : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	ASDTCollectible();
	virtual void BeginPlay() override;

	void Collect();
	void OnCooldownDone();
	bool IsOnCooldown();
	//void InitializeAudioComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float m_CollectCooldownDuration = 10.f;

	USoundCue* pickupAudioCue;

	//UAudioComponent* pickupAudioComponent;

protected:
	FTimerHandle m_CollectCooldownTimer;


};
