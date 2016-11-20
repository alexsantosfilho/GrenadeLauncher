// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InimigoC.generated.h"

UCLASS()
class MYPROJECT2_API AInimigoC : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInimigoC();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


private:

	UPROPERTY(EditAnywhere)
		UBoxComponent* Root;
	//	UPROPERTY(EditAnywhere)
	//	UStaticMeshComponent* MeshComp;
	//	UPROPERTY(EditAnywhere)
	//	UStaticMeshComponent* MeshComp2;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Particle;
	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* ProjectileMovement;

	float DefaultZ;
	float DamageAmount = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = Tick)
		float RunningTime;



	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};