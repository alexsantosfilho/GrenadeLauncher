// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MyProject2.h"
#include "MyProject2Character.h"
#include "MyProject2Projectile.h"
#include "AIPatrol.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Item.h"
#include "Alavanca.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/DestructibleActor.h"
#include "ProjectActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);


const FName AMyProject2Character::LookUpBinding("LookUp");
const FName AMyProject2Character::LookRightBinding("Turn");

//////////////////////////////////////////////////////////////////////////
// AMyProject2Character

AMyProject2Character::AMyProject2Character()
{

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	// Create a CameraComponent	
	InternalCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	InternalCamera->SetupAttachment(GetCapsuleComponent());
	InternalCamera->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	InternalCamera->bUsePawnControlRotation = true;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = true;
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(InternalCamera);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AMyProject2Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	FTimerHandle handle;
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); //Attach gun mesh component to Skeleton, doing it here because the skelton is not yet created in the constructor
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyProject2Character::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);


	InputComponent->BindAction("Crouch", IE_Pressed, this, &AMyProject2Character::StartCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &AMyProject2Character::StopCrouch);


	InputComponent->BindAction("Pause", IE_Pressed, this, &AMyProject2Character::Pause);



	InputComponent->BindAction("Show", IE_Pressed, this, &AMyProject2Character::ShowPontuacao);

	InputComponent->BindAction("Run", IE_Pressed, this, &AMyProject2Character::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &AMyProject2Character::StopRun);

	InputComponent->BindAction("Drop", IE_Pressed, this, &AMyProject2Character::DropProjectActor);



	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyProject2Character::TouchStarted);
	if (EnableTouchscreenMovement(InputComponent) == false)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMyProject2Character::OnFire);
	}

	InputComponent->BindAxis("MoveForward", this, &AMyProject2Character::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyProject2Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AMyProject2Character::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AMyProject2Character::LookUpAtRate);

	InputComponent->BindAction("SwitchCamera", IE_Pressed, this, &AMyProject2Character::OnToggleCamera);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &AMyProject2Character::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AMyProject2Character::TouchStopped);

	InputComponent->BindAction("Collect", IE_Pressed, this, &AMyProject2Character::OnCollect);

}

void AMyProject2Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void AMyProject2Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void AMyProject2Character::StartRun() {
	GetCharacterMovement()->MaxWalkSpeed = 3000;

}
void AMyProject2Character::StopRun() {
	GetCharacterMovement()->MaxWalkSpeed = 1500;

}


void AMyProject2Character::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AMyProject2Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			//^aqui o problema
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

}

void AMyProject2Character::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AMyProject2Character::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = false;
}

void AMyProject2Character::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
	{
		if (TouchItem.bIsPressed)
		{
			if (GetWorld() != nullptr)
			{
				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
				if (ViewportClient != nullptr)
				{
					FVector MoveDelta = Location - TouchItem.Location;
					FVector2D ScreenSize;
					ViewportClient->GetViewportSize(ScreenSize);
					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.X * BaseTurnRate;
						AddControllerYawInput(Value);
					}
					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
					{
						TouchItem.bMoved = true;
						float Value = ScaledDelta.Y * BaseTurnRate;
						AddControllerPitchInput(Value);
					}
					TouchItem.Location = Location;
				}
				TouchItem.Location = Location;
			}
		}
	}
}

void AMyProject2Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyProject2Character::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
		//	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());

	}
}

void AMyProject2Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyProject2Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AMyProject2Character::EnableTouchscreenMovement(class UInputComponent* InputComponent)
{
	bool bResult = false;
	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		bResult = true;
		InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyProject2Character::BeginTouch);
		InputComponent->BindTouch(EInputEvent::IE_Released, this, &AMyProject2Character::EndTouch);
		InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMyProject2Character::TouchUpdate);
	}
	return bResult;
}

void AMyProject2Character::DropProjectActor() {

	DropProjectServer();

}


void AMyProject2Character::DropProjectServer_Implementation() {


	FActorSpawnParameters SpawnParameters;
	UWorld* World = GetWorld();

	if (World != nullptr) {
		const FRotator Rotation = Controller->GetControlRotation();

		AProjectActor* proj = World->SpawnActor<AProjectActor>(GetActorLocation(), Rotation, SpawnParameters);
		FVector NewVelocity = GetActorForwardVector() * 5000.f;
	//	AudioComp->SetSound(FireSound);
		//AudioComp->Play();
		//ProjectileClass->Velocity = FVector(NewVelocity);

		if (proj != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Spawm1 ok!"));
		}
	}


}

bool AMyProject2Character::DropProjectServer_Validate() {

	return true;
}

void AMyProject2Character::ShowPontuacao() {
	UE_LOG(LogTemp, Warning, TEXT("%d"), Pontuacao);
}

void AMyProject2Character::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {



	if (OtherActor->IsA(AAIPatrol::StaticClass())) {

		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("destruiu o principal"));
	}

	/*
	if ((OtherActor != nullptr) && (OtherActor != this) &&
		(OtherComp != nullptr) && (OtherActor->IsA(AProAGranada::jectActor:StaticClass()))) {

		AMyProject2Projectile* MyProject2Character = Cast<AMyProject2Projectile>(OtherActor);

		UE_LOG(LogTemp, Warning, TEXT("Destruiu Parwwwwwwwabens"));
		Destroy();

	}
	*/

}

void AMyProject2Character::OnToggleCamera()
{
	UE_LOG(LogTemp, Warning, TEXT("carro"));

	EnableIncarView(!bInCarCameraActive);
}

void AMyProject2Character::EnableIncarView(const bool bState, const bool bForce)
{
	if ((bState != bInCarCameraActive) || (bForce == true))
	{
		bInCarCameraActive = bState;

		if (bState == true)
		{
			FollowCamera->Deactivate();
			InternalCamera->Activate();
			Mesh1P->Activate();
			UE_LOG(LogTemp, Warning, TEXT("InternalCamera"));

		}
		else
		{
			Mesh1P->Activate();
			InternalCamera->Deactivate();
			FollowCamera->Activate();
			UE_LOG(LogTemp, Warning, TEXT("FollowCamera"));

		}


	}
}

void AMyProject2Character::Tick(float Delta)
{
	Super::Tick(Delta);

	// controla a camera e tudo da camera 2
	if ((InputComponent) && (bInCarCameraActive == true))
	{

		FRotator HeadRotation = InternalCamera->RelativeRotation;
		//HeadRotation.Pitch += InputComponent->GetAxisValue(LookUpBinding);
		HeadRotation.Yaw += InputComponent->GetAxisValue(LookRightBinding);
		InternalCamera->RelativeRotation = HeadRotation;
	}

	if (GetMesh()->GetAnimationMode() == EAnimationMode::AnimationSingleNode
		&& GetCharacterMovement()->IsMovingOnGround() && CanCrouch() == true) {
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	}
}


void AMyProject2Character::SetColetavelLife(int NewColetavelLife) {
	ColetavelLife = NewColetavelLife;

}
int AMyProject2Character::GetColetavelLife() {
	return ColetavelLife;
}


void AMyProject2Character::OnDeath() {

	UWorld* World = GetWorld();
	if (ColetavelLife <= 0 && World != nullptr && JumpAnim != nullptr) {
		GetMesh()->PlayAnimation(JumpAnim, false);
		//FVector InitialLocation(-7414.0f, 137.002579f, 226.001587f);
		ColetavelLife;
		TimerManager();

		//SetActorLocation(InitialLocation);
		UE_LOG(LogTemp, Warning, TEXT("Voce morreu!3"));
		//UGameplayStatics::OpenLevel(World, "NewMap5");
	}

}


void AMyProject2Character::TimerManager() {

	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this,
		&AMyProject2Character::TimerManager, 1.0f, true);
	CountdownTime -= 1.0f; //<- problema do contador aqui

	if (CountdownTime <= -2.005f) {
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("Time Out"));
		UWorld* World = GetWorld();
		if (World != nullptr) {

			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
			if (PlayerController != nullptr && UserWidget != NULL) {
				PlayerController->SetPause(true);
				UUserWidget* UserW = UWidgetBlueprintLibrary::Create(World, UserWidget, PlayerController);

				if (UserW != nullptr) {
					UserW->AddToViewport();
					PlayerController->bShowMouseCursor = true;
				}

			}

		}
		//Destroy();
		// FVector InitialLocation(-3640.0f, -40.002f, 218.0012f);
		//SetActorLocation(InitialLocation);
	}
}



void AMyProject2Character::OnCollect() {
	TArray<AActor*> AtoresColetados;
	CollectCollisionComp->GetOverlappingActors(AtoresColetados);

	for (int i = 0; i < AtoresColetados.Num(); i++) {
		if (AtoresColetados[i]->IsA(AItem::StaticClass())) {
			AItem* ItemColetado = Cast<AItem>(AtoresColetados[i]);
			Inventory.Add(ItemColetado);
			ItemColetado->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("%d"), Inventory.Num());
		}
		else if (AtoresColetados[i]->IsA(AAlavanca::StaticClass())) {
			AAlavanca* Alavanca = Cast<AAlavanca>(AtoresColetados[i]);
			Alavanca->OnPressed();
		}
	}
}



void AMyProject2Character::Pause() {

	UWorld* World = GetWorld();
	if (World != nullptr) {

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
		if (PlayerController != nullptr && UserWidget != NULL) {
			PlayerController->SetPause(true);
			UUserWidget* UserW = UWidgetBlueprintLibrary::Create(World, UserWidget, PlayerController);

			if (UserW != nullptr) {
				UserW->AddToViewport();
				PlayerController->bShowMouseCursor = true;
			}

		}

	}

}


void AMyProject2Character::Jump() {
	Super::Jump();

	if (JumpAnim != nullptr) {
		GetMesh()->PlayAnimation(JumpAnim, false);
	}

	else if (JumpAnim == nullptr) {

		MoveForward(true);

	}
}



void AMyProject2Character::Crouch(bool bClientSimulation)
{
	Super::Crouch();
	if (JumpAnim2 != nullptr) {
		GetMesh()->PlayAnimation(JumpAnim2, false);
	}

}

void AMyProject2Character::StartCrouch()
{
	Crouch();
}

void AMyProject2Character::StopCrouch()
{
	UnCrouch();
}
