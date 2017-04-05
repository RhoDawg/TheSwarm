// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

/**
*
*/
UCLASS()
class THESWARM_API ACharacterController : public APlayerController
{
	GENERATED_BODY()


public:

	ACharacterController();
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	UFUNCTION(BlueprintCallable, Category = "Setup")
		virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void ClearInputActionBindings();


public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Character Info", meta = (AllowPrivateAccess = "true"))
		APawn* ControlledCharacterReference; //initialized in BeginPlay()


};
