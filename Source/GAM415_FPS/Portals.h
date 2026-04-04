// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/BoxComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/ArrowComponent.h"
#include "Portals.generated.h"

class GAM415_FPSCharacter;

UCLASS()
class GAM415_FPS_API APortals : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortals();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

		//Heather: This is the static mesh component for the portal. It will be used to render the portal in the world.
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

		//Heather: This is the screen capture component for the portal. It will be used to capture the scene from the perspective of the portal and render it on the portal's surface.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* sceneCapture;

		//Heather: This is the arrow component for the portal. It will be used to indicate the direction of the portal and help with debugging.
	UPROPERTY(EditAnywhere)
	UArrowComponent* rootArrow;

		//Heather: This is the render target for the portal. It will be used to render the scene from the perspective of the portal.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextureRenderTarget2D* renderTarget;

		//Heather: This is the box component for the portal. It will be used to detect when the player enters the portal.
	UPROPERTY(EditAnywhere)
	UBoxComponent* boxComp;

		//Heather: This is a reference to the other portal. It will be used to teleport the player from one portal to the other.
	UPROPERTY(EditAnywhere)
	APortals* OtherPortal;

		//Heather: This is a material interface for the portal. It will be used to render the portal's surface with the scene captured by the scene capture component.
	UPROPERTY(EditAnywhere)
	UMaterialInterface* mat;

		//Heather: This Function will be called when the player enters the portal.
	UFUNCTION()
	void OnOverLapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		//Heather: This Function will be used to set the boolean variable that will be used to determine if the player is in the portal or not.
	UFUNCTION()
	void SetBool(AGAM415_FPSCharacter* playerChar);

		//Heather: This Function will be used to update the portal's scene capture component and render target to render the scene from the perspective of the portal.
	UFUNCTION()
	void UpdatePortals();

};
