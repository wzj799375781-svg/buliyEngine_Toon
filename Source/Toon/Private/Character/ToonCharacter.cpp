// buliy


#include "Character/ToonCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AToonCharacter::AToonCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate =FRotator(0.0f,400.0f,0.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}


// PlayerCamera-Begin 2-3
void AToonCharacter::GetCameraParameters_Implementation(float& TP_FOV, bool& RightShoulder)
{
	TP_FOV = ThirdPersonFOV;
	RightShoulder = rightShoulder;
}

void AToonCharacter::Get3PPivotTarget_Implementation(FTransform& OutTransform)
{
	OutTransform = GetActorTransform();
}

void AToonCharacter::Get3PTraceParams_Implementation(FVector& TraceOrigin, float& TraceRadius,
	TEnumAsByte<ETraceTypeQuery>& TraceChannel)
{
	TraceOrigin = GetActorLocation();
	TraceRadius = 10.0f;
	TraceChannel = ETraceTypeQuery::TraceTypeQuery1;
}

void AToonCharacter::GetEssentialValues_Implementation(FVector& Velocity, FVector& Accele, FVector& MovementInput,
	bool& IsMoving, bool& HasMovementInput, float& Speed, float& MovementInputAmount, FRotator& AimingRotation,
	float& AimYawRate)
{
	IToonCharacterInterface::GetEssentialValues_Implementation(Velocity, Accele, MovementInput, IsMoving,
	                                                           HasMovementInput, Speed, MovementInputAmount,
	                                                           AimingRotation,
	                                                           AimYawRate);
}

void AToonCharacter::GetCurrentStates_Implementation(TEnumAsByte<EMovementMode>& PawnMovementMode,
	EMovementState& MovementState, EMovementState& PrevMovementState, ERotationMode& RotationMode, EGait& ActualGait,
	EStance& ActualStance, EOverlayState& OverlayState)
{
	PawnMovementMode = GetCharacterMovement()->MovementMode;
	MovementState =movementState;
	PrevMovementState = prevMovementState;
	RotationMode = rotationMode;
	ActualGait = Gait;
	ActualStance = Stance;
	OverlayState =overlayState;
}

// PlayerCamera-End 2025/10/20

