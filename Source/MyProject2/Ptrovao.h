// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Ptrovao.generated.h"

UCLASS()
class MYPROJECT2_API APtrovao : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APtrovao();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


private:

	UPROPERTY(EditAnywhere)
		UBoxComponent* Root;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Particle;
	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* ProjectileMovement;


	UPROPERTY(VisibleAnywhere, Category = Tick)
		float RunningTime;


};
