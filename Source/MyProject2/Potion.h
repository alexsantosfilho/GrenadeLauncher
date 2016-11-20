// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Potion.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API APotion : public AItem
{
	GENERATED_BODY()
	
	
public:
	APotion();

	virtual int Use() override;


};