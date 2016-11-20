// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProjectActor.generated.h"

UCLASS()
class MYPROJECT2_API AProjectActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(EditAnywhere)
		FVector Velocity = FVector(600.f);
	float BulletExpiry = 0;

	UPROPERTY(EditAnywhere)
		UAnimSequence* JumpAnim;

private:
	UPROPERTY(EditAnywhere)
		UBoxComponent* Root;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Particle;
	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* ProjectileMovement;

	float DefaultY;
	float DefaultX;
	float DefaultZ;

	UPROPERTY(EditAnywhere)
		float DamageAmount = 1.0f;




	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere, Category = Tick)
		float RunningTime;


};