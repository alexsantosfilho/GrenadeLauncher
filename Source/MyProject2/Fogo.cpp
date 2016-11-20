// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "Fogo.h"
#include "Lixeira.h"
#include "MyProject2Character.h"




// Sets default values
AFogo::AFogo()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("BlockAllDynamic");
	ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));
	if (Mesh.Succeeded()) {
		MeshComp->SetStaticMesh(Mesh.Object);
	}
	MeshComp->SetWorldScale3D(FVector(0.7f, 0.7f, 0.7f));
	MeshComp->OnComponentHit.AddDynamic(this, &AFogo::OnHit);
	MeshComp->SetupAttachment(RootComponent);


	Particle = CreateDefaultSubobject<UParticleSystemComponent>
		(TEXT("Particle"));
	Particle->bAutoActivate = true;
	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		ParticleSystem(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	if (ParticleSystem.Succeeded()) {
		Particle->SetTemplate(ParticleSystem.Object);
	}
	Particle->SetupAttachment(RootComponent);
	Particle->ToggleActive();


	//	InitialLifeSpan = 1.0f;
}

// Called when the game starts or when spawned
void AFogo::BeginPlay()
{
	Super::BeginPlay();

	DefaultX = GetActorLocation().X;
	DefaultY = GetActorLocation().Y;
	DefaultZ = GetActorLocation().Z;

}

// Called every frame
void AFogo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	Location.X = DefaultX;
	Location.Y = DefaultY;
	Location.Z = DefaultZ;

	SetActorLocation(Location);

	//RunningTime += DeltaTime;
	//float DestroyTime = 0.8f * RunningTime;
	//if (DestroyTime > 0.9f) {
	//Destroy();
	//}
}

void AFogo::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	if ((OtherActor != nullptr) && (OtherActor != this) &&
		(OtherComp != nullptr) && (OtherActor->IsA(AMyProject2Character::StaticClass()))) {

		AMyProject2Character* MyProject2Character = Cast<AMyProject2Character>(OtherActor);
	//	MyProject2Character->SetColetavelLife(MyProject2Character->GetColetavelLife() - DamageAmount);
	//	MyProject2Character->OnDeath();
	//	UE_LOG(LogTemp, Warning, TEXT("Life = %d"), MyProject2Character->GetColetavelLife());

		//Destroy();

		UE_LOG(LogTemp, Warning, TEXT("Encostou"));
	}

}