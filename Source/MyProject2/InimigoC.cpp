// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "InimigoC.h"
#include "MyProject2Character.h"
#include "AIPatrol.h"



// Sets default values
AInimigoC::AInimigoC()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Root->SetCollisionProfileName("BlockAllDynamic");
	Root->bGenerateOverlapEvents = true;
	Root->OnComponentHit.AddDynamic(this, &AInimigoC::OnHit);

	RootComponent = Root;



	//MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	//MeshComp->SetCollisionProfileName("BlockAllDynamic");
	//ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));
	//	if (Mesh.Succeeded()) {
	//	MeshComp->SetStaticMesh(Mesh.Object);
	//}
	//	MeshComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	//MeshComp->OnComponentHit.AddDynamic(this, &AInimigoC::OnHit);
	//MeshComp->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = Root;
	ProjectileMovement->InitialSpeed = 300.0f;
	ProjectileMovement->MaxSpeed = 500.0f;

}

// Called when the game starts or when spawned
void AInimigoC::BeginPlay()
{
	Super::BeginPlay();

	DefaultZ = GetActorLocation().Z;
}

// Called every frame
void AInimigoC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector Location = GetActorLocation();
	Location.Z = DefaultZ;
	SetActorLocation(Location);

	RunningTime += DeltaTime;
	float DestroyTime = 0.5f * RunningTime;
	if (DestroyTime > 1.f) {
		Destroy();
	}
}

void AInimigoC::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor != nullptr &&
		OtherActor->IsA(AMyProject2Character::StaticClass()) &&
		OtherComp != nullptr) {

		AMyProject2Character* MyProject2Character = Cast<AMyProject2Character>(OtherActor);
//		MyProject2Character->SetColetavelLife(MyProject2Character->GetColetavelLife() - DamageAmount);
	//	MyProject2Character->OnDeath();
	//	UE_LOG(LogTemp, Warning, TEXT("Life = %d"), MyProject2Character->GetColetavelLife());

		Destroy();

		UE_LOG(LogTemp, Warning, TEXT("Encostou"));
	}
}