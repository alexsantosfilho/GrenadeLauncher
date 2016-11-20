// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MyProject2.h"
#include "MyProject2Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/DestructibleActor.h"
#include "AIPatrol.h"



// Sets default values
AMyProject2Projectile::AMyProject2Projectile()
{

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AMyProject2Projectile::OnHit);		// set up a notification for when this component hits something blocking

																				// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyProject2Projectile::OnOverlapBegin);


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

void AMyProject2Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this))
	{

		OnDetonate();
		UE_LOG(LogTemp, Warning, TEXT("OnHit"));


	}
}

void AMyProject2Projectile::BeginPlay()
{

	Super::BeginPlay();

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyProject2Projectile::OnDetonate, 5.f, false);
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

}


void AMyProject2Projectile::OnDetonate()
{
	UParticleSystemComponent* Explosion = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticles, GetActorTransform());
	Explosion->SetRelativeScale3D(FVector(4.f));

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());

//	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	
	TArray<FHitResult> HitActors;

	FVector StartTrace = GetActorLocation();
	FVector EndTrace = StartTrace;
	EndTrace.Z += 300.f;

	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(Radius);

	if (GetWorld()->SweepMultiByChannel(HitActors, StartTrace, EndTrace, FQuat::FQuat(), ECC_WorldStatic, CollisionShape))
	{
		for (auto Actors = HitActors.CreateIterator(); Actors; Actors++) {

			UStaticMeshComponent* SM = Cast<UStaticMeshComponent>((*Actors).Actor->GetRootComponent());
			ADestructibleActor* DA = Cast<ADestructibleActor>((*Actors).GetActor());

			if (SM) {
				SM->AddRadialImpulse(GetActorLocation(), 1000.f, 5000.f, ERadialImpulseFalloff::RIF_Linear, true);

			}
			else if (DA) {
				DA->GetDestructibleComponent()->ApplyRadiusDamage(10.f, Actors->ImpactPoint, 500.f, 3000.f, false);

			}

		}

	}
	UE_LOG(LogTemp, Warning, TEXT("OnDetonate"));

	Destroy();
}


void AMyProject2Projectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {



	if ((OtherActor != nullptr) && (OtherActor != this) &&
		(OtherComp != nullptr) && (OtherActor->IsA(AAIPatrol::StaticClass()))) {

		AAIPatrol* MyProject2Character = Cast<AAIPatrol>(OtherActor);
		MyProject2Character->SetColetavelLife2(MyProject2Character->GetColetavelLife2() - DamageAmount); // DANO NO PERSONAGEM
		MyProject2Character->OnDeath2();
		//	MyProject2Character->OnDeath3();


		UE_LOG(LogTemp, Warning, TEXT("Granada DANO NO INIMIGO"));

	}


}
