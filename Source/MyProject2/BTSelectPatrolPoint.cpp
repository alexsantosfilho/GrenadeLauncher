// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject2.h"
#include "BTSelectPatrolPoint.h"
#include "AIPatrolPoint.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAIPatrolController* AICon = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());

	if (AICon) {
		/*Get bb component */

		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();

		AAIPatrolPoint* CurrentPoint = Cast<AAIPatrolPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvaliblePatrolPoints = AICon->GetPatrolPoints();

		AAIPatrolPoint* NextPatroiPoint = nullptr;

		if (AICon->CurrentPatrolPont != AvaliblePatrolPoints.Num() - 1) {

			NextPatroiPoint = Cast<AAIPatrolPoint>(AvaliblePatrolPoints[++AICon->CurrentPatrolPont]);
		}
		else // if there is not any more points to go to
		{
			NextPatroiPoint = Cast<AAIPatrolPoint>(AvaliblePatrolPoints[0]);
			AICon->CurrentPatrolPont = 0;
		}

		BlackboardComp->SetValueAsObject("LocationToGo", NextPatroiPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
