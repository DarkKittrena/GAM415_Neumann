// Fill out your copyright notice in the Description page of Project Settings.


#include "Portals.h"
#include "GAM415_FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortals::APortals()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

		//Heather: These statements set up the components for the portal.
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture"));
	rootArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Root Arrow"));

		//Heather: These statements set up the attachment of the components.
	RootComponent = boxComp;
	mesh->SetupAttachment(boxComp);
	sceneCapture->SetupAttachment(mesh);
	rootArrow->SetupAttachment(boxComp);

		//Heather: This statement sets up the collision for the box component.
	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);

}

// Called when the game starts or when spawned
void APortals::BeginPlay()
{
	Super::BeginPlay();

		//Heather: This statement binds the OnOverLapBegin function to the OnComponentBeginOverlap event of the box component.
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortals::OnOverLapBegin);

		//Heather: These statements set up the properties of the scene capture component to render the scene from the perspective of the portal and render it on the portal's surface.
	mesh->SetHiddenInSceneCapture(true);
	mesh->CastShadow = false;


		//Heather: This statement sets the material of the mesh component to the material variable.
	if(mat)
	{
		mesh->SetMaterial(0, mat);
	}
}

// Called every frame
void APortals::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

		//Heather: This statement calls the UpdatePortals function every frame to update the portal's surface with the scene captured by the scene capture component.
	UpdatePortals();

}

void APortals::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		//Heather: This statement casts the OtherActor to the player character class to check if the player has entered the portal.
	AGAM415_FPSCharacter* playerChar = Cast<AGAM415_FPSCharacter>(OtherActor);
	
		//Heather: This statement checks if the cast was successful, if the other portal is valid, and if the player is not already teleporting.
	if(playerChar)
	{
		if (OtherPortal) 
		{
			if(!playerChar->isTeleporting)
			{

					//Heather: This statement sets the isTeleporting boolean variable of the player character to true to prevent multiple teleports from happening at the same time before getting the loctaion of the other portal and teleporting the player to that location.
				playerChar->isTeleporting = true;
				FVector loc = OtherPortal->rootArrow->GetComponentLocation();
				playerChar->SetActorLocation(loc);

					//Heather: This statement sets a timer to call the SetBool function after 1 second to set the isTeleporting boolean variable of the player character back to false to allow the player to teleport again.
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDel;
				TimerDel.BindUFunction(this, FName("SetBool"), playerChar);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 1, false);
			}
		}
	}
}

void APortals::SetBool(AGAM415_FPSCharacter* playerChar)
{
	if(playerChar)
	{
		playerChar->isTeleporting = false;
	}
}

void APortals::UpdatePortals()
{
		//Heather: These statements calculate the location and rotation for the scene capture component to render the scene from the perspective of the portal and set the world location and rotation of the scene capture component to that location and rotation.
	FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation();
	FVector camLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	FRotator camRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();
	FVector CombinedLocation = camLocation + Location;

	sceneCapture->SetWorldLocationAndRotation(CombinedLocation, camRotation);
}

