// Fill out your copyright notice in the Description page of Project Settings.

/* --< Includes >-- */
#include "PuzzlePlatformsGameInstance.h"
#include "PuzzlePlatformsCharacter.h"
#include "Blueprint/UserWidget.h"
#include "UI/MainMenuWidget.h"
#include "OnlineSessionSettings.h"
#include "UI/MenuWidget.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

const static FName SESSION_NAME = TEXT("My Session Game");

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
}

void UPuzzlePlatformsGameInstance::Init()
{
    IOnlineSubsystem* Oss = IOnlineSubsystem::Get();

    if(Oss != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("OSS Recieved: %s"), *Oss->GetSubsystemName().ToString());
        SessionInterface = Oss->GetSessionInterface();
        if(SessionInterface.IsValid())
        {
            SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
            SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
            SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnFindSessionComplete);
            SessionSearch = MakeShareable(new FOnlineSessionSearch());
            if(SessionSearch.IsValid())
            {
                SessionSearch->bIsLanQuery = true;
                // SessionSearch->QuerySettings.
                UE_LOG(LogTemp, Warning, TEXT("Start Finding Sessions"));
                SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
            }
        }
    }
    else
        UE_LOG(LogTemp, Warning, TEXT("Found No OSS"));
}

/* --< Functions >-- */
    /* --< Commands >-- */
void UPuzzlePlatformsGameInstance::LoadMenuWidget()
{
    if (!ensure(MainMenuClass != nullptr)) return;
    
    Menu = CreateWidget<UMainMenuWidget>(this, MainMenuClass);
    if (!ensure(Menu != nullptr)) return;

    Menu->Setup();
    Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::InGameLoadMenu()
{
    if (!ensure(InGameMenuClass != nullptr)) return;

    InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
    if (!ensure(InGameMenu != nullptr)) return;

    InGameMenu->SetupInGame();
    InGameMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::InGameDisappear()
{
    if (!ensure(InGameMenuClass != nullptr)) return;
    if (!ensure(InGameMenu != nullptr)) return;
    if(InGameMenu != nullptr)
        InGameMenu->TearDown();
}

void UPuzzlePlatformsGameInstance::Host()
{
    if(SessionInterface.IsValid())
    {
        auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
        if(ExistingSession != nullptr)
        {
            SessionInterface->DestroySession(SESSION_NAME);
        }
        else
        {
           CreateSession();
        }
    }
}

void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
    if(!Success)
    {
        UE_LOG(LogTemp, Warning, TEXT("Could Not Create Seesionn"));
        return;
    }
    
    if(Menu != nullptr)
        Menu->TearDown();
    
    GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Hosting"));
    
    UWorld* World = GetWorld();
    if (!ensure(World != nullptr)) return;
    
    World->ServerTravel("/Game/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
    if(Success)
    {
        CreateSession();
    }
}

void UPuzzlePlatformsGameInstance::OnFindSessionComplete(bool Success)
{
    if(Success && SessionSearch.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Done Finding Sessions"));
        for(auto& SearchResult : SessionSearch->SearchResults)
        {
            UE_LOG(LogTemp, Warning, TEXT("Found session name: %s"), *SearchResult.GetSessionIdStr());
        }
    }
}

void UPuzzlePlatformsGameInstance::CreateSession()
{
    if(SessionInterface.IsValid())
    {
        FOnlineSessionSettings SessionSettings;
        SessionSettings.bIsLANMatch = true;
        SessionSettings.NumPublicConnections = 2;
        SessionSettings.bShouldAdvertise = true;
        SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
    }
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
    if(Menu != nullptr)
        Menu->TearDown();
    
    GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;
        
    PlayerController->ClientTravel(Address, TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::ReturnToMenu()
{
    if(InGameMenu != nullptr)
        InGameMenu->TearDown();

    GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Returing to Main Menu"));

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (!ensure(PlayerController != nullptr)) return;
    
    UWorld* World = GetWorld();
    if (!ensure(World != nullptr)) return;

    if(PlayerController->HasAuthority())
        World->ServerTravel("/Game/Maps/MainMenu", true);
    
    PlayerController->ClientTravel("/Game/Maps/MainMenu",TRAVEL_Absolute);
    
}

void UPuzzlePlatformsGameInstance::Quit()
{
    FGenericPlatformMisc::RequestExit(false);
}


