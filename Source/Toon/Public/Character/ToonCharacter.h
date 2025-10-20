// buliy

#pragma once

#include "CoreMinimal.h"
#include "Character/ToonCharacterBase.h"
#include "Data/Locomotion/ToonLocomotionData.h"
#include "Interface/ToonCameraInterface.h"
#include "Interface/ToonCharacterInterface.h"
#include "ToonCharacter.generated.h"


/**
 * 
 */
UCLASS()
class TOON_API AToonCharacter : public AToonCharacterBase,public IToonCameraInterface,public IToonCharacterInterface
{
	GENERATED_BODY()

	public:
	AToonCharacter();

	//TODO:应该修改成表格读取数据而不是直接设置
	// PlayerCamera-Begin 2-1
	UPROPERTY(EditAnywhere, Category = "CameraSystem")
	float ThirdPersonFOV = 90.0f;
	UPROPERTY(EditAnywhere, Category = "CameraSystem")
	float FirstPersonFOV = 90.0f;
	UPROPERTY(EditAnywhere, Category = "CameraSystem")
	bool  rightShoulder = false;
	// PlayerCamera-End 2025/10/20

	// PlayerAnimation-Begin 
	UPROPERTY(BlueprintReadOnly, Category = "References")
	TObjectPtr<UAnimInstance> MainAnimInstance;
	// PlayerAnimation-End 2025/10/20

	//LocomotionSystem-Begin 2-1
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MovementSystem")
	FDataTableRowHandle MovementModel;

	UPROPERTY(BlueprintReadOnly, Category = "MovementSystem")
	FMovementSettingsState rowData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateValues")
	EMovementState movementState;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateValues")
	EMovementState prevMovementState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	EGait DesiredGait;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateValues")
	EGait Gait;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateValues")
	ERotationMode rotationMode;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	ERotationMode DesiredRotationMode;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateValues")
	EOverlayState overlayState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	EStance DesiredStance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateValues")
	EStance Stance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rotation System")
	FRotator TargetRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EssentialInformation")
	FRotator LastVelocityRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EssentialInformation")
	FRotator LastMovementInputRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EssentialInformation")
	FVector Acceleration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CachedVariables")
	FVector PreviousVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EssentialInformation")
	float speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EssentialInformation")
	bool isMoving;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EssentialInformation")
	float movementInputAmount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EssentialInformation")
	bool hasMovementInput=false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EssentialInformation")
	float aimYawRate=0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CachedVariables")
	float PreviousAimYaw =0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MovementSystem")
	FMovementSettings CurrentMovementSettings;

	//LocomotionSystem-End 2025/10/20


public:
	// PlayerCamera-Begin 2-2
	virtual void GetCameraParameters_Implementation(float& TP_FOV, bool& RightShoulder)  override;
	virtual void Get3PPivotTarget_Implementation(FTransform& OutTransform)override;
	virtual void Get3PTraceParams_Implementation(FVector& TraceOrigin, float& TraceRadius, TEnumAsByte<ETraceTypeQuery>& TraceChannel)override;
	// PlayerCamera-End 2025/10/20

	// LocomotionSystem-Begin 2-2
	virtual void GetEssentialValues_Implementation(FVector& Velocity, FVector& Accele, FVector& MovementInput, bool& IsMoving, bool& HasMovementInput
		, float& Speed, float& MovementInputAmount, FRotator& AimingRotation, float& AimYawRate)override;

	virtual void GetCurrentStates_Implementation(TEnumAsByte<EMovementMode>& PawnMovementMode, EMovementState& MovementState, EMovementState& PrevMovementState, ERotationMode& RotationMode
		, EGait& ActualGait, EStance& ActualStance, EOverlayState& OverlayState)override;
	// LocomotionSystem-End 2025/10/20
};


