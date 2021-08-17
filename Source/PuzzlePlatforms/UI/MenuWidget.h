// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/* --< Includes >-- */
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/* --< Classes >-- */
class IMenuInterface;

UCLASS()
class PUZZLEPLATFORMS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
/* --< Functions >-- */
	/* --< Setters >-- */
	void SetMenuInterface(IMenuInterface* AMenuInterface);

	void Setup();
	void SetupInGame();
	void TearDown();

protected:
/* --< Pointers >-- */
	IMenuInterface* MenuInterface;
	
};
