// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/* --< Includes >-- */
#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
/* --< Constructor >-- */
	AMovingPlatform();
	
	virtual void Tick(float DeltaTime) override;

/* --< Functions >-- */
	void AddActiveTrigger();
	void RemoveActiveTrigger();
	
protected:
	 virtual void BeginPlay() override;

private:	
/* --< Variables >-- */
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
	
	/* --< UProperties >-- */
	UPROPERTY(EditAnywhere)
		float MoveSpeed = 20.f;
	UPROPERTY(EditAnywhere)
		int ActiveTriggers = 1;
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
		FVector TargetLocation;
};
