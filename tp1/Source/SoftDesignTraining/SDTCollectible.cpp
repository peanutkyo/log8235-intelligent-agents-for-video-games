// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SDTCollectible.h"

ASDTCollectible::ASDTCollectible()
{
	static ConstructorHelpers::FObjectFinder<USoundCue> audioClip(TEXT("SoundCue'/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue'"));
	pickupAudioCue = audioClip.Object;
}

void ASDTCollectible::BeginPlay()
{
	Super::BeginPlay();

	//InitializeAudioComponent();
}

void ASDTCollectible::Collect()
{
	GetWorld()->GetTimerManager().SetTimer(m_CollectCooldownTimer, this, &ASDTCollectible::OnCooldownDone, m_CollectCooldownDuration, false);

	if (GetStaticMeshComponent()->IsVisible()) {
		UGameplayStatics::PlaySound2D(this, pickupAudioCue);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString("AI PICKED UP A POWER-UP!"));
	}

	GetStaticMeshComponent()->SetVisibility(false);
}

void ASDTCollectible::OnCooldownDone()
{
	GetWorld()->GetTimerManager().ClearTimer(m_CollectCooldownTimer);

	GetStaticMeshComponent()->SetVisibility(true);
}

bool ASDTCollectible::IsOnCooldown()
{
	return m_CollectCooldownTimer.IsValid();
}

/*void ASDTCollectible::InitializeAudioComponent()
{
// Store a reference to the Cue asset - we'll need it later.
static ConstructorHelpers::FObjectFinder<USoundCue> pickupAudioWave(TEXT("SoundCue'/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue'"));
//UGameplayStatics::PlaySound2D(this, pickupAudioWave.Object);


// Create an audio component, the audio component wraps the Cue, and allows us to ineract with
// it, and its parameters from code.
pickupAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PickupAudioComp"));

// I don't want the sound playing the moment it's created.
pickupAudioComponent->bAutoActivate = false; // don't play the sound immediately.

// I want the sound to follow the pawn around, so I attach it to the Pawns root.
pickupAudioComponent->SetupAttachment(RootComponent);

if (pickupAudioWave.Object) {
pickupAudioComponent->SetSound(pickupAudioWave.Object);
}
}*/
