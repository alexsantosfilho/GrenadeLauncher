// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "Rotatable.h"


// Sets default values
ARotatable::ARotatable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotatableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RotatableMesh"));

	AnimTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("AnimationTrigger"));
	AnimTrigger->bGenerateOverlapEvents = true;
	AnimTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARotatable::OnAnimTriggered);
	//AnimTrigger->AttachToComponent(RotatableMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);


}

// Called when the game starts or when spawned
void ARotatable::BeginPlay()
{
	Super::BeginPlay();

	if (AnimCurve) {

		FOnTimelineFloat ProgressFunction;

		ProgressFunction.BindUFunction(this, FName("HandleProgress"));

		MyTimeline.AddInterpFloat(AnimCurve, ProgressFunction);
		MyTimeline.SetLooping(false);

		ActorInitialRotation = TargetRotation = GetActorRotation();



		if (RotationAxis == "Yaw") {

			TargetRotation.Yaw += MaxRotation;

		}

		else if (RotationAxis == "Pitch") {
			TargetRotation.Pitch += MaxRotation;


		}
		else if (RotationAxis == "Roll") {

			TargetRotation.Roll += MaxRotation;

		}
	}
}

// Called every frame
void ARotatable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MyTimeline.TickTimeline(DeltaTime);

}

void ARotatable::HandleProgress(float Value)
{

	FRotator NewRotation = FMath::Lerp(ActorInitialRotation, TargetRotation, Value);
	SetActorRotation(NewRotation);
}

void ARotatable::OnAnimTriggered(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (!MyTimeline.IsPlaying()) {
		MyTimeline.PlayFromStart();

	}
}