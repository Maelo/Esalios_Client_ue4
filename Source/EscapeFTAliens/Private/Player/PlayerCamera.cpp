// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCamera.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
APlayerCamera::APlayerCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent0"));
	RootComponent = Root;

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement0"));
	FloatingMovement->MaxSpeed = 1200;

	// Create a camera and attach to boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	Camera->SetupAttachment(Root);
	Camera->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

}

// Called when the game starts or when spawned
void APlayerCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCamera::MoveRight(float Val)
{
	AddMovementInput(FVector(0.f, 1.f, 0.f), Val);
}

void APlayerCamera::MoveUp(float Val)
{
	AddMovementInput(FVector(1.f, 0.f, 0.f),Val);
}

// Called every frame
void APlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("CameraRight", this, &APlayerCamera::MoveRight);
	PlayerInputComponent->BindAxis("CameraUp", this, &APlayerCamera::MoveUp);

}

