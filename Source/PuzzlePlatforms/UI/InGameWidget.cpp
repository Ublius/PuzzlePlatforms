// Fill out your copyright notice in the Description page of Project Settings.

/* --< Includes >-- */
#include "InGameWidget.h"
#include "Components/Button.h"
#include "MenuInterface.h"

bool UInGameWidget::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    if (!ensure(CancelInGameMenuButton != nullptr)) return false;
    CancelInGameMenuButton->OnClicked.AddDynamic(this, &UInGameWidget::BackToGame);

    if (!ensure(ReturnMenuInGameMenuButton != nullptr)) return false;
    ReturnMenuInGameMenuButton->OnClicked.AddDynamic(this, &UInGameWidget::ReturnToMainMenu);
    
    return true;
}

/* --< Functions >-- */
void UInGameWidget::BackToGame()
{
    TearDown();
}

void UInGameWidget::ReturnToMainMenu()
{
    if(MenuInterface != nullptr)
        MenuInterface->ReturnToMenu();
}
