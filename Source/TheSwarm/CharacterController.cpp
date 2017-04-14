// Fill out your copyright notice in the Description page of Project Settings.

#include "TheSwarm.h"
#include "PlayerCharacter.h"
#include "CharacterController.h"




ACharacterController::ACharacterController()
{


}

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	ControlledCharacterReference = GetPawn();
	SetupInputComponent();
}

void ACharacterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//Raycast every frame
	Raycast();
}

void ACharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	auto * ControlledCharacter = ControlledCharacterReference;

	if (ControlledCharacter)
	{
		if (ControlledCharacter->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
		{
			if (GEngine)
			{
				// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("Loading CharacterController"));
			}
			//****INPUT ACTIONS****/

			InputComponent->BindAction("Jump", IE_Pressed, Cast<APlayerCharacter>(ControlledCharacter), &ACharacter::Jump);
			InputComponent->BindAction("Jump", IE_Released, Cast<APlayerCharacter>(ControlledCharacter), &ACharacter::StopJumping);

			InputComponent->BindAction("Sprint", IE_Pressed, Cast<APlayerCharacter>(ControlledCharacter), &APlayerCharacter::ToggleSprint);
			InputComponent->BindAction("Sprint", IE_Released, Cast<APlayerCharacter>(ControlledCharacter), &APlayerCharacter::ToggleSprint);

			InputComponent->BindAction("ToggleView", IE_Pressed, Cast<APlayerCharacter>(ControlledCharacter), &APlayerCharacter::ToggleView);

			/****INPUT AXIS****/

			InputComponent->BindAxis("MoveForward", Cast<APlayerCharacter>(ControlledCharacter), &APlayerCharacter::MoveForward);
			InputComponent->BindAxis("MoveRight", Cast<APlayerCharacter>(ControlledCharacter), &APlayerCharacter::MoveRight);

			InputComponent->BindAxis("Turn", Cast<APlayerCharacter>(ControlledCharacter), &APawn::AddControllerYawInput);
			InputComponent->BindAxis("LookUp", Cast<APlayerCharacter>(ControlledCharacter), &APawn::AddControllerPitchInput);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Controlled Pawn"));
	}

}

void ACharacterController::ClearInputActionBindings()
{
	InputComponent->ClearActionBindings();
}

void ACharacterController::Raycast()
{
	//Calculating start and end location
	if (ControlledCharacterReference)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Character Reference = True"));
		if (ControlledCharacterReference->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Controlled Character Reference = True"));
			UCameraComponent* FirstPersonCameraComponent = Cast<APlayerCharacter>(ControlledCharacterReference)->GetFirstPersonCameraComponent();
			FVector StartLocation = FirstPersonCameraComponent->GetComponentLocation();
			FVector EndLocation = StartLocation + (FirstPersonCameraComponent->GetForwardVector() * RaycastRange);

			FHitResult RaycastHit;

			//Raycast should ignore the character
			FCollisionQueryParams CQP;
			CQP.AddIgnoredActor(this);

			//Raycast
			GetWorld()->LineTraceSingleByChannel(RaycastHit, StartLocation, EndLocation, ECollisionChannel::ECC_WorldDynamic, CQP);


			AItem* InteractableItem = Cast<AItem>(RaycastHit.GetActor());

			if (LastItemSeen && LastItemSeen != InteractableItem)
			{
				//If our character sees a different pickup then disable the glowing effect on the previous seen item
				LastItemSeen->SetGlowEffect(false);
			}

			if (InteractableItem)
			{
				//Enable the glow effect on the current item
				LastItemSeen = InteractableItem;
				InteractableItem->SetGlowEffect(true);
			}//Re-Initialize 
			else LastItemSeen = nullptr;
		}
	}
	else
	{

		UE_LOG(LogTemp, Warning, TEXT("Controlled Character Reference = FALSE"));
	}
}

