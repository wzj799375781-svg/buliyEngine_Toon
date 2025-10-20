// buliy


#include "Player/ToonPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Player/ToonPlayerCameraManager.h"

AToonPlayerController::AToonPlayerController()
{
	bReplicates = true;
}

void AToonPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AToonPlayerCameraManager* CameraManager =Cast<AToonPlayerCameraManager>(PlayerCameraManager))
	{
		CameraManager->OnPossess(InPawn);
	}
}

void AToonPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(ToonContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(ToonContext,0);
}

void AToonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent  = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AToonPlayerController::Move);
}

void AToonPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator  Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}
