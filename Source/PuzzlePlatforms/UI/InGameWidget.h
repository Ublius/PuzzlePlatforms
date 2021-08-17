// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/* --< Includes >-- */
#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "InGameWidget.generated.h"

/* --< Classes >-- */
class UButton;

UCLASS()
class PUZZLEPLATFORMS_API UInGameWidget : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;
	
private:
/* --< Pointers >-- */
	/* --< UProperties >-- */
	UPROPERTY(meta = (BindWidget))
		UButton* CancelInGameMenuButton;
	UPROPERTY(meta = (BindWidget))
		UButton* ReturnMenuInGameMenuButton;

/* --< Functions >-- */
	/* --< UFunctions >-- */
	UFUNCTION()
		void BackToGame();
	UFUNCTION()
		void ReturnToMainMenu();
};
