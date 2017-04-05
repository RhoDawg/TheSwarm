// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class THESWARM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Pawn mesh: 1st person view (arms; seen only by self) */
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	/*Third person Mesh*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Mesh3P;

	/**Third Person Spring Arm*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* TPCameraBoom;


	/**Third Person Camera*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* ThirdPersonCameraComponent;



public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Movement)
		bool bIsSprinting;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float WalkSpeed;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float RunSpeed;




	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement Functions
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/** Handles Sprint Movement**/
	UFUNCTION(Reliable, Server, WithValidation)
		void ToggleSprint();
	void ToggleSprint_Implementation();
	bool ToggleSprint_Validate();

	/**Toggle FP<->TP view**/
	virtual void ToggleView();



public:


	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns Mesh3P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh3P() const { return Mesh3P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	/** Returns ThirdPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetThirdPersonCameraComponent() const { return ThirdPersonCameraComponent; }

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
		bool bIsFirstPersonView; //initilized in constructor


};
