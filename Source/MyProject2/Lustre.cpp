// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "Lustre.h"
#include "Luz.h"



// Sets default values
ALustre::ALustre()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Root->SetCollisionProfileName("BlockAllDynamic");
	RootComponent = Root;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoCollision");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/3dsmax/iluminação.iluminação'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/3dsmax/Material__25.Material__25'"));
	if (Material.Succeeded()) {
		MeshComp->SetMaterial(0, Material.Object);
	}
	MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -30.0f));
	MeshComp->SetWorldScale3D(FVector(1.5f, 0.7f, 0.7f));
	MeshComp->SetupAttachment(RootComponent);
}



// Called when the game starts or when spawned
void ALustre::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALustre::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;
	float ShootTime = 1.0f * RunningTime;
	if (ShootTime > 2.0f) {
		FActorSpawnParameters SpawnParameters;
		UWorld* World = GetWorld();
		if (World != nullptr) {
			FRotator Rotation = MeshComp->GetComponentRotation();
			ALuz* Proj = World->SpawnActor<ALuz>
				(GetActorLocation(), Rotation,
					SpawnParameters);
			if (Proj != nullptr) {

				RunningTime = 0.0f;
			}

		}

	}
}