// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AIPatrol.generated.h"

UCLASS()
class MYPROJECT2_API AAIPatrol : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIPatrol();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void Tick(float DeltaSeconds) override;


	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = AI)
		class UPawnSensingComponent* PawnSensingComp;


	void SetColetavelLife2(int NewColetavelLife2);
	int GetColetavelLife2();

	virtual void OnDeath2();

	virtual void OnDeath3();


	//UPROPERTY(EditAnywhere, Category = AI)
	//UTextRenderComponent* MyText;

	//	void MakeTextFacePlayer();

	//	UPROPERTY(EditAnywhere)
	//UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UAnimSequence* JumpAnim;

	UPROPERTY(EditAnywhere)
		UAnimSequence* JumpAnim2;

	void TimerManager();

	void TimerManager2();

	float Animou = 5.f;


private:
	FTimerHandle CountdownTimerHandle;

	float CountdownTime;


	UFUNCTION()
		void OnPlayerCaught(APawn* Pawn);

	int ColetavelLife2 = 5; // numero de vidas do inimigo

	UPROPERTY(EditAnywhere)
		UShapeComponent* Root;

	TSubclassOf<class UUserWidget> UserWidget;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = Tick)
		float RunningTime;
	UPROPERTY(EditAnywhere)
		float DamageAmount = 1.0f; // quantidade de dano que a colisao da bala tira
								   //UFUNCTION()
								   //void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
								   //			FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);




	//UFUNCTION()
	// void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};