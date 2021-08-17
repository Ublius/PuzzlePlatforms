// Fill out your copyright notice in the Description page of Project Settings.

/* --< Includes >-- */
#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;

    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if(HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }

    GlobalStartLocation = GetActorLocation();
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(ActiveTriggers > 0)
    {
        if(HasAuthority())
        {
            FVector Location = GetActorLocation();
            float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
            float JourneyTraveled = (Location - GlobalStartLocation).Size();
        
            if(JourneyTraveled >= JourneyLength)
            {
                FVector Swap = GlobalStartLocation;
                GlobalStartLocation = GlobalTargetLocation;
                GlobalTargetLocation = Swap;
            }
        
            const FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
            Location += MoveSpeed * DeltaTime * Direction;
            SetActorLocation(Location);      
        }
    }
}

/* --< Functions >-- */
void AMovingPlatform::AddActiveTrigger()
{
    ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
    if(ActiveTriggers > 0)
        ActiveTriggers--;
}


