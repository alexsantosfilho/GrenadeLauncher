// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "AIPatrolController.h"
#include "AIPatrol.h"
#include "AIPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"


AAIPatrolController::AAIPatrolController()
{

	/* Initialize blackboard and behavior Tree*/

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	/* Initialize blackboard Keys*/
	PlayerKey = "Target";
	LocationToGoKey = "LocationToGo";


	CurrentPatrolPont = 0;


}

void AAIPatrolController::SetPlayerCaught(APawn * Pawn)
{
	if (BlackboardComp) {
		BlackboardComp->SetValueAsObject(PlayerKey, Pawn);
	}

}



void AAIPatrolController::Possess(APawn * Pawn)
{

	Super::Possess(Pawn);


	/* Get reference to the Character*/

	AAIPatrol* AICharacter = Cast<AAIPatrol>(Pawn);

	if (AICharacter) {


		if (AICharacter->BehaviorTree->BlackboardAsset) {
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}

		/* Populate patrol point array*/
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), PatrolPoints);

		BehaviorComp->StartTree(*AICharacter->BehaviorTree);

	}
}

