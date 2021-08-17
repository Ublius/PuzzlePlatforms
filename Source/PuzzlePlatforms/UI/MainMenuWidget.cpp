// Fill out your copyright notice in the Description page of Project Settings.

/* --< Includes >-- */
#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "MenuInterface.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/EditableTextBox.h"
#include "ServerRow.h"


UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer)
{
    ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/UI/WBP_ServerRow"));
    if (!ensure(ServerRowBPClass.Class != nullptr)) return;
    ServerRowClass = ServerRowBPClass.Class;
}

bool UMainMenuWidget::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    if (!ensure(HostButton != nullptr)) return false;
    HostButton->OnClicked.AddDynamic(this, &UMainMenuWidget::HostServer);
    
    if (!ensure(JoinButton != nullptr)) return false;
    JoinButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenJoinMenu);

    if (!ensure(QuitMainMenuButton != nullptr)) return false;
    QuitMainMenuButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);

    if (!ensure(ConnectButton != nullptr)) return false;
    ConnectButton->OnClicked.AddDynamic(this, &UMainMenuWidget::JoinServer);

    if (!ensure(CancelJoinMenuButton != nullptr)) return false;
    CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenMainMenu);
    
    return true;
}

/* --< Functions >-- */
void UMainMenuWidget::HostServer()
{
        if(MenuInterface != nullptr)
            MenuInterface->Host();
}

void UMainMenuWidget::JoinServer()
{   
    if(MenuInterface != nullptr)
    {
        // if (!ensure(IPBar != nullptr)) return;
        // const FString Address = IPBar->GetText().ToString();
        //
        // if(Address.Equals(FString()))
        //     return;
        //
        // MenuInterface->Join(Address);
        UWorld* World = this->GetWorld();
        if (!ensure(World != nullptr)) return;
        
        USeverRow* Row = CreateWidget<USeverRow>(World, ServerRowClass);
        if (!ensure(Row != nullptr)) return;

        ServerList->AddChild(Row);
        
    }
}

void UMainMenuWidget::QuitGame()
{
    if(MenuInterface != nullptr)
        MenuInterface->Quit();
}

void UMainMenuWidget::OpenJoinMenu()
{
    if (!ensure(MenuSwitcher != nullptr)) return;
    if (!ensure(JoinMenu != nullptr)) return;
    MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenuWidget::OpenMainMenu()
{
    if (!ensure(MenuSwitcher != nullptr)) return;
    if (!ensure(MainMenu != nullptr)) return;
    MenuSwitcher->SetActiveWidget(MainMenu);
}        