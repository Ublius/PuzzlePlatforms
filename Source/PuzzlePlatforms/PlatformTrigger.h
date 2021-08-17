// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/* --< Includes >-- */
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformTrigger.generated.h"

/* --< Classes >-- */
class UBoxComponent;
class AMovingPlatform;

UCLASS()
class PUZZLEPLATFORMS_API APlatformTrigger : public AActor
{
	GENERATED_BODY()
	
public:
/* --< Constructor >-- */
	APlatformTrigger();

	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

private:
/* --< Pointers >-- */
	/* --< UProperties >-- */
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* TriggerVolume;
	UPROPERTY(EditAnywhere)
		TArray<AMovingPlatform*> PlatformsToTrigger;

/* --< Functions >-- */
	/* --< UFunctions >-- */
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
