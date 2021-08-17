// Fill out your copyright notice in the Description page of Project Settings.

/* --< Includes >-- */
#include "MenuWidget.h"
#include "MenuInterface.h"

/* --< Functions >-- */
    /* --< Setters >-- */
void UMenuWidget::SetMenuInterface(IMenuInterface* AMenuInterface)
{
    this->MenuInterface = AMenuInterface;
}

void UMenuWidget::Setup()
{
    UWorld* World = GetWorld();
    if (!ensure(World != nullptr)) return;
    
    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr)) return;
    
    PlayerController->SetActorHiddenInGame(true);
    APawn* PlayerPawn = PlayerController->GetPawn();
    PlayerPawn->SetActorHiddenInGame(true);
    
    this->AddToViewport();
    
    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::SetupInGame()
{
    UWorld* World = GetWorld();
    if (!ensure(World != nullptr)) return;
    
    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr)) return;
    
    this->AddToViewport();
    
    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::TearDown()
{
    UWorld* World = GetWorld();
    if (!ensure(World != nullptr)) return;
    
    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr)) return;

    this->RemoveFromViewport();

    FInputModeGameOnly InputModeData;
    
    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = false;
}
