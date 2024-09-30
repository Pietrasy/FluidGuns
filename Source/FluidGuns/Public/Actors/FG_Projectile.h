// Copyright Pietras

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FG_Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class FLUIDGUNS_API AFG_Projectile : public AActor
{
	GENERATED_BODY()

public:
	AFG_Projectile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Projectile")
	UProjectileMovementComponent* ProjectileComponent = nullptr;

	UPROPERTY(EditAnywhere, Category="Projectile")
	USphereComponent* SphereCollision = nullptr;
};
