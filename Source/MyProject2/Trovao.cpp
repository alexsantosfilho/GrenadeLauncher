// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "Trovao.h"
#include "Ptrovao.h"



// Sets default values
ATrovao::ATrovao()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	//	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	//	Root->SetCollisionProfileName("BlockAllDynamic");
	//	RootComponent = Root;
	//	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	//	MeshComp->SetCollisionProfileName("NoCollision");

	//MeshComp->SetWorldLocation(FVector(0.0f, 0.0f, -30.0f));
	//MeshComp->SetWorldScale3D(FVector(1.5f, 0.7f, 0.7f));
	//MeshComp->AttachTo(RootComponent);
}



// Called when the game starts or when spawned
void ATrovao::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATrovao::Tick(float DeltaTime) {
	//Super::Tick(DeltaTime);
	//RunningTime += DeltaTime;
	//float ShootTime = 1.0f * RunningTime;
	//if (ShootTime > 11.0f) {
	//	FActorSpawnParameters SpawnParameters;
	//UWorld* World = GetWorld();
	//if (World != nullptr) {
	//	FRotator Rotation = MeshComp->GetComponentRotation();
	//	APtrovao* Proj = World->SpawnActor<APtrovao>
	//	(GetActorLocation(), Rotation,
	//		SpawnParameters);
	//	if (Proj != nullptr) {
	//
	//		RunningTime = 0.0f;
	//	}
	//	if (FireSound != NULL)
	//{
	//				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	//	}

	//	}

	//}
}