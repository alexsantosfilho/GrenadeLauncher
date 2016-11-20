// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AIPatrolController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AAIPatrolController : public AAIController
{
	GENERATED_BODY()
	

		/*bEHAVIOR TREE COMPONENT */
		UBehaviorTreeComponent* BehaviorComp;


	/* Our Blackboard Component*/

	UBlackboardComponent* BlackboardComp;

	/*Blackboard Keys*/
	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName LocationToGoKey;

	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName PlayerKey;

	TArray<AActor*> PatrolPoints;

	virtual void Possess(APawn* Pawn) override;


public:

	AAIPatrolController();

	void SetPlayerCaught(APawn* Pawn);


	int32 CurrentPatrolPont = 0;

	/*iNLINE GETTER FUNCIOONS */

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray< AActor*> GetPatrolPoints() const { return PatrolPoints; }


};
