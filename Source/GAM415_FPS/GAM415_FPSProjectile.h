// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAM415_FPSProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS(config=Game)
class AGAM415_FPSProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

		//Heather: Adds a static mesh to the projectile
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ballMesh;

		//Heather: Adds a material to the projectile
	UPROPERTY(EditAnywhere)
	UMaterial* baseMat;

		//Heather: Adds a random color to the projectile
	UPROPERTY()
	FLinearColor randColor;

		//Heather: Adds a material instance to the projectile
	UPROPERTY(EditAnywhere)
	UMaterialInterface* projMat;

		//Heather: Adds a dynamic material instance to the projectile
	UPROPERTY()
	UMaterialInstanceDynamic* dmiMat;

		//Heather: Adds a particle system to the projectile
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* colorP;

public:
	AGAM415_FPSProjectile();

protected:
	virtual void BeginPlay();

public:

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

