// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OBJWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAM415_FPS_API UOBJWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateOBJRifle(bool bObtainedRifle);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateOBJenemies(float enemieskilled);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateOBJPortal(float portalactivated);
	
};
