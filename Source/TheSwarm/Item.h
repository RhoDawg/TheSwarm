// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class THESWARM_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	/*Enables/Disables the glow effect on the pickup*/
	void SetGlowEffect(bool Status);

	/*Returns the Texture of our Pickup*/
	FORCEINLINE UTexture2D* GetItemImage() { return ItemImage; }

protected:
	/*The Static Mesh of the Item*/
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ItemSM;

	/*The Texture of the item in case we want to add it in the secrets or inventory*/
	UPROPERTY(EditAnywhere, Category = "ItemProperties")
		UTexture2D* ItemImage;

	/*The name of the item*/
	UPROPERTY(EditAnywhere, Category = "ItemProperties")
		FString ItemName;
	
};
