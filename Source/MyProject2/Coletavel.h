// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Coletavel.generated.h"

UCLASS()
class MYPROJECT2_API AColetavel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AColetavel();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

private:

	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
		int Valor;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};