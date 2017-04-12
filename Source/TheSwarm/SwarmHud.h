// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "SwarmHud.generated.h"

/**
 * 
 */
UCLASS()
class THESWARM_API ASwarmHud : public AHUD
{
	GENERATED_BODY()
public:
	ASwarmHud();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
	
	
	
};
