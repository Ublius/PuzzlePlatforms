// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/* --< Includes >-- */
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/* --< Classes >-- */
class UUserWidget;
class UMainMenuWidget;
class UInGameWidget;
class UMenuWidget;
class UKismetSystemLibrary;
class FOnlineSessionSearch;
// class IOnlineSessionPtr;

UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	/* --< Constructor >-- */
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

/* --< Functions >-- */
	/* --< UFunctions >-- */
		/* --< Commands >-- */
	UFUNCTION(BlueprintCallable)
		void LoadMenuWidget();
	UFUNCTION(BlueprintCallable)
		void InGameLoadMenu();
	UFUNCTION(BlueprintCallable)
		void InGameDisappear();
	UFUNCTION(Exec)
		void Host();
	UFUNCTION(Exec)
		void Join(const FString& Address);
	UFUNCTION(Exec)
		void ReturnToMenu();
	UFUNCTION(Exec)
		void Quit();

private:
/* --< Pointers >-- */
	UMainMenuWidget* Menu;
	UMenuWidget* InGameMenu;
	UKismetSystemLibrary* test;
	
/* --< Variables >-- */
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
	/* --< UProperties >-- */
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> MainMenuClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> InGameMenuClass;

/* --< Functions >-- */
	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionComplete(bool Success);
	void CreateSession();
};
