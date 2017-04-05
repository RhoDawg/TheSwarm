// Fill out your copyright notice in the Description page of Project Settings.

#include "TheSwarm.h"
#include "PlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "UnrealNetwork.h"
#include "GameFramework/InputSettings.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	bIsSprinting = false;
	WalkSpeed = 600.0f;
	RunSpeed = 1200.0f;

	GetCharacterMovement()->MaxAcceleration = WalkSpeed;



	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	/****************************************************************************************************/
	/*First Person Setup*/
	/***************************************************************************************************/

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->Activate(false);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);




	/****************************************************************************************************/
	/*Third Person Setup*/
	/***************************************************************************************************/

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh3P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh3P"));
	Mesh3P->SetOwnerNoSee(true);
	Mesh3P->SetupAttachment(GetCapsuleComponent());
	Mesh3P->bCastDynamicShadow = true;
	Mesh3P->CastShadow = true;


	//Create a Spring Arm Component
	TPCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonSpringArm"));
	TPCameraBoom->SetupAttachment(Mesh3P);
	TPCameraBoom->TargetOffset = FVector(0.f, 0.f, 0.f);
	TPCameraBoom->SetRelativeLocation(FVector(-40.f, 0.f, 160.f));
	TPCameraBoom->SetRelativeRotation(FRotator(-10.f, 0.f, 0.f));
	TPCameraBoom->SetupAttachment(GetCapsuleComponent()); // attach it to the third person mesh
	TPCameraBoom->TargetArmLength = 200.f;
	TPCameraBoom->bEnableCameraLag = false;
	TPCameraBoom->bEnableCameraRotationLag = false;
	TPCameraBoom->bUsePawnControlRotation = true; // let the controller handle the view rotation
	TPCameraBoom->bInheritYaw = true;
	TPCameraBoom->bInheritPitch = true;
	TPCameraBoom->bInheritRoll = false;


	// Create a CameraComponent	
	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCameraComponent->SetupAttachment(TPCameraBoom);
	ThirdPersonCameraComponent->bUsePawnControlRotation = false;
	ThirdPersonCameraComponent->FieldOfView = 90.f;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	FirstPersonCameraComponent->SetActive(true);
	ThirdPersonCameraComponent->SetActive(false);
	bIsFirstPersonView = true;

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//****INPUT ACTIONS****/

	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	////PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::ToggleSprint);
	//PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::ToggleSprint);

	//PlayerInputComponent->BindAction("ToggleView", IE_Pressed, this, &APlayerCharacter::ToggleView);

	/****INPUT AXIS****/

	//PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

//SetupNetworking
void APlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(APlayerCharacter, bIsSprinting);
}

//move front or back
void APlayerCharacter::MoveForward(float value)
{

	if (value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

//Move left or right
void APlayerCharacter::MoveRight(float value)
{
	if (value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), value);
	}

}

bool APlayerCharacter::ToggleSprint_Validate()
{
	return true;
}

//toggle sprinting state
void APlayerCharacter::ToggleSprint_Implementation()
{


	if (bIsSprinting)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		//UE_LOG(LogTemp, Warning, TEXT("Stopped Sprinting, current Speed: %f"), GetCharacterMovement()->MaxWalkSpeed);

	}
	else
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		//UE_LOG(LogTemp, Warning, TEXT("Sprinted Pressed, current Speed: %f"), GetCharacterMovement()->MaxWalkSpeed);
	}


}

//Swap between first and third person view
void APlayerCharacter::ToggleView()
{

	FirstPersonCameraComponent->SetActive(!bIsFirstPersonView);
	ThirdPersonCameraComponent->SetActive(bIsFirstPersonView);
	Mesh3P->SetOwnerNoSee(!bIsFirstPersonView);
	Mesh1P->SetOwnerNoSee(bIsFirstPersonView);
	bIsFirstPersonView = !bIsFirstPersonView;

}
