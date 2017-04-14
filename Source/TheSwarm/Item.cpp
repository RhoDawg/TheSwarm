// Fill out your copyright notice in the Description page of Project Settings.

#include "TheSwarm.h"
#include "Item.h"


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Initializing our properties
	ItemSM = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemSM"));

	ItemImage = CreateDefaultSubobject<UTexture2D>(FName("ItemImage"));
	ItemSM->CustomDepthStencilValue = STENCIL_ITEMHIGHLIGHT;
	

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	//SetGlowEffect(true);
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AItem::SetGlowEffect(bool Status)
{
	ItemSM->SetRenderCustomDepth(Status);
}

