// Fill out your copyright notice in the Description page of Project Settings.

/* --< Includes >-- */
#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"

/* --< Constructor >-- */
APlatformTrigger::APlatformTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	RootComponent = TriggerVolume;
}

void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/* --< Functions >-- */
void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for(AMovingPlatform* MovingPlatform : PlatformsToTrigger)
	{
		MovingPlatform->AddActiveTrigger();
	}
}

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for(AMovingPlatform* MovingPlatform : PlatformsToTrigger)
	{
		MovingPlatform->RemoveActiveTrigger();
	}
}



