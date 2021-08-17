// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/* --< Includes >-- */
#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenuWidget.generated.h"

/* --< Classes >-- */
class UButton;
class IMenuInterface;
class UWidgetSwitcher;
class UEditableTextBox;
class UUserWidget;

UCLASS()
class PUZZLEPLATFORMS_API UMainMenuWidget : public UMenuWidget
{
	GENERATED_BODY()

public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual bool Initialize() override;
	
private:
	TSubclassOf<UUserWidget> ServerRowClass;
	
	/* --< UProperties >-- */
	UPROPERTY(meta = (BindWidget))
		UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
		UButton* JoinButton;
	UPROPERTY(meta = (BindWidget))
		UButton* QuitMainMenuButton;
	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* MenuSwitcher;
	UPROPERTY(meta = (BindWidget))
		UWidget* JoinMenu;
	UPROPERTY(meta = (BindWidget))
		UWidget* MainMenu;
	UPROPERTY(meta = (BindWidget))
		UButton* ConnectButton;
	UPROPERTY(meta = (BindWidget))
		UButton* CancelJoinMenuButton;
	UPROPERTY(meta = (BindWidget))
		UPanelWidget* ServerList;

/* --< Functions >-- */
	/* --< UFunctions >-- */
	UFUNCTION()
		void HostServer();
	UFUNCTION()
		void JoinServer();
	UFUNCTION()
		void QuitGame();
	UFUNCTION()
		void OpenJoinMenu();
	UFUNCTION()
		void OpenMainMenu();
	

};
