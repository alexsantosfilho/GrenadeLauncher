// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "Ptrovao.h"
#include "Trovao.h"
#include "MyProject2Character.h"



// Sets default values
APtrovao::APtrovao()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Root->SetCollisionProfileName("OverlapAllDynamic");
	Root->bGenerateOverlapEvents = true;

	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");

	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -30.0f));
	MeshComp->SetWorldScale3D(FVector(100.0f, 100.5f, 100.5f));
	MeshComp->SetupAttachment(RootComponent);

	//Particle = CreateDefaultSubobject<UParticleSystemComponent>
	//	(TEXT("Particle"));
	//	Particle->bAutoActivate = true;
	//static ConstructorHelpers::FObjectFinder<UParticleSystem>
	//	ParticleSystem(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/Lightning/P_LineToPoint_Blast_Lightning_00.P_LineToPoint_Blast_Lightning_00'"));
	//	if (ParticleSystem.Succeeded()) {
	//		Particle->SetTemplate(ParticleSystem.Object);
	//	}
	//	Particle->SetupAttachment(RootComponent);
	//Particle->ToggleActive();

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = Root;
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;

	InitialLifeSpan = 5.0f;
}

// Called when the game starts or when spawned
void APtrovao::BeginPlay()
{
	Super::BeginPlay();

	//DefaultX = GetActorLocation().X;
}

// Called every frame
void APtrovao::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	RunningTime += DeltaTime;
	float DestroyTime = 1.0f * RunningTime;
	if (DestroyTime > 2.0f) {
		Destroy();
	}
}

