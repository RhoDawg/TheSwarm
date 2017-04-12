// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class THESWARM_API IInteractable
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
		void InteractWith();
	
	
};
