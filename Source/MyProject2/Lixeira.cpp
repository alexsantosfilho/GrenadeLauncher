// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "Lixeira.h"
#include "Fogo.h"


// Sets default values
ALixeira::ALixeira()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//
	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Root->SetCollisionProfileName("BlockAllDynamic");
	RootComponent = Root;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/3dsmax/lixo.lixo'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/3dsmax/NewMaterial2.NewMaterial2'"));
	if (Material.Succeeded()) {
		MeshComp->SetMaterial(0, Material.Object);
	}
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -30.0f));
	MeshComp->SetWorldScale3D(FVector(1.5f, 0.7f, 0.7f));
	MeshComp->SetupAttachment(RootComponent);



	Particle = CreateDefaultSubobject<UParticleSystemComponent>
		(TEXT("Particle"));
	Particle->bAutoActivate = true;
	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		ParticleSystem(TEXT("ParticleSystem'/Game/particulas/P_Fire.P_Fire'"));
	if (ParticleSystem.Succeeded()) {
		Particle->SetTemplate(ParticleSystem.Object);
	}
	Particle->SetupAttachment(RootComponent);
	Particle->ToggleActive();
}



// Called when the game starts or when spawned
void ALixeira::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALixeira::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;
	float ShootTime = 1.0f * RunningTime;
	if (ShootTime > 2.0f) {
		FActorSpawnParameters SpawnParameters;
		UWorld* World = GetWorld();
		if (World != nullptr) {
			FRotator Rotation = MeshComp->GetComponentRotation();
			AFogo* Proj = World->SpawnActor<AFogo>
				(GetActorLocation(), Rotation,
					SpawnParameters);
			if (Proj != nullptr) {

				RunningTime = 0.0f;
			}

		}

	}
}