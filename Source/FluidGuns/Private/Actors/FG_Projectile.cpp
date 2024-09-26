// Copyright Pietras


#include "Actors/FG_Projectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AFG_Projectile::AFG_Projectile()
{
	// Actor will not call Tick() every frame.
	PrimaryActorTick.bCanEverTick = false;
	// Create sphere component, set it as root component and set its collision profile.
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollision);
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileComponent");
}