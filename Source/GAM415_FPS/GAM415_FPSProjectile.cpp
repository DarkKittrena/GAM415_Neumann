// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM415_FPSProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PerlinProcTerrain.h"

AGAM415_FPSProjectile::AGAM415_FPSProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AGAM415_FPSProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

		// Heather: Adds a static mesh to the projectile
	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));

	// Set as root component
	RootComponent = CollisionComp;

		//Heather: Attaches the static mesh to the root component
	ballMesh->SetupAttachment(CollisionComp);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AGAM415_FPSProjectile::BeginPlay()
{
	Super::BeginPlay();

		//Heather: Creates a random color for the projectile
	randColor = FLinearColor(UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f), UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f), UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f), 1.f);

		//Heather: Creates a dynamic material instance for the projectile
	dmiMat = UMaterialInstanceDynamic::Create(projMat, this);

		//Heather: Sets the material of the projectile to the dynamic material instance
	ballMesh->SetMaterial(0, dmiMat);

		//Heather: Sets the random color parameter of the dynamic material instance
	dmiMat->SetVectorParameterValue("ProjColor", randColor);
}

void AGAM415_FPSProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

		//Heather: Checks if the projectile has hit something other than itself
	if(OtherActor != nullptr)
	{
			//Heather: Checks if the particle system is valid
		if (colorP)
		{
				//Heather: Spawns the particle system at the location of the hit and sets the random color parameter of the particle system
			UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, HitComp, NAME_None, FVector(-20.f, 0.f, 0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);
			particleComp->SetNiagaraVariableLinearColor(FString("RandomColor"), randColor);

				//Heather: Destroys the projectile's static mesh and sets the collision profile to "NoCollision" to prevent further collisions
			ballMesh->DestroyComponent();
			CollisionComp->BodyInstance.SetCollisionProfileName("NoCollision");
		}

			//Heather: Sets a random frame number for the decal material instance
		float frameNum = UKismetMathLibrary::RandomFloatInRange(0.0f, 3.0f);

			//Heather: Spawns a decal at the hit location with a random size and rotation based on the hit normal
		auto decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), baseMat, FVector(UKismetMathLibrary::RandomFloatInRange(20.f, 40.f)), Hit.Location, Hit.Normal.Rotation(), 0.f);
		auto MatInst = decal->CreateDynamicMaterialInstance();

			//Heather: Sets the random color and frame number parameters of the decal material instance
		MatInst->SetVectorParameterValue("Color", randColor);
		MatInst->SetScalarParameterValue("Frame", frameNum);

			//Heather: Checks if the other actor is a procedural terrain actor
		APerlinProcTerrain* procTerrain = Cast<APerlinProcTerrain>(OtherActor);

			//Heather: If the other actor is a procedural terrain actor, call the AlterMesh function of the procedural terrain actor and pass in the impact point of the hit
		if (procTerrain) 
		{
			procTerrain->AlterMesh(Hit.ImpactPoint);
		}
	}
}