// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "ColetavelLife.h"
#include "MyProject2Character.h"


// Sets default values
AColetavelLife::AColetavelLife()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USphereComponent >(TEXT("Root"));
	Root->bGenerateOverlapEvents = true;
	Root->SetCollisionProfileName("OverlapAllDynamic");
	Root->OnComponentBeginOverlap.AddDynamic(this, &AColetavelLife::OnOverlapBegin);
	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionProfileName("NoColision");
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AColetavelLife::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AColetavelLife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AColetavelLife::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->IsA(AMyProject2Character::StaticClass()))) {

		AMyProject2Character* MyProject2Character = Cast<AMyProject2Character>(OtherActor);
	//	MyProject2Character->SetColetavelLife(MyProject2Character->GetColetavelLife() + ColetavelLife);
		//UE_LOG(LogTemp, Warning, TEXT("ColetavelLife = %d /10"), MyProject2Character->GetColetavelLife());
		Destroy();
	}


}
