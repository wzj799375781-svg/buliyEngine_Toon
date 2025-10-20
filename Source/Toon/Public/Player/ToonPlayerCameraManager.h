// buliy
// PlayerCamera-Begin
#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "Data/Locomotion/ToonLocomotionData.h"
#include "ToonPlayerCameraManager.generated.h"




/**
 * 
 */
UCLASS()
class TOON_API AToonPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
public:
	AToonPlayerCameraManager();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Pawn")
	TObjectPtr<APawn> ControlledPawn;
	FTransform PivotTarget;
	float  TPFOV;
	FVector PivotLocation;
	FVector TargetCameraLocation;
	FRotator TargetCameraRotation;
	FTransform SmoothedPivotTarget;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Info")
	EMovementState MovmentState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Info")
	ERotationMode RotationMode;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Info")
	EGait Gait;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Info")
	EStance Stance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Info")
	bool rightShoulder;

	
protected:
	UPROPERTY(BlueprintReadWrite, Category = "Camera Paramet")
	float  PivotOffset_X;
	UPROPERTY(BlueprintReadWrite, Category = "Camera Paramet")
	float  PivotOffset_Y;
	UPROPERTY(BlueprintReadWrite, Category = "Camera Paramet")
	float  PivotOffset_Z;
	UPROPERTY(BlueprintReadWrite, Category = "Camera Paramet")
	float  PivotLagSpeed_X;
	UPROPERTY(BlueprintReadWrite, Category = "Camera Paramet")
	float  PivotLagSpeed_Y;
	UPROPERTY(BlueprintReadWrite, Category = "Camera Paramet")
	float  PivotLagSpeed_Z;
	UPROPERTY(BlueprintReadWrite, Category = "Camera Paramet")
	float  CameraOffset_X;
	UPROPERTY(BlueprintReadWrite, Category = "Camera Paramet")
	float  CameraOffset_Y;
	UPROPERTY(BlueprintReadWrite, Category = "Camera Paramet")
	float  CameraOffset_Z;
	UPROPERTY(BlueprintReadWrite, Category = "Camera Paramet")
	float RotationLagSpeed;
	


public:
	void OnPossess(APawn* NewPawn);
	void CustomCameraBehavior(FVector* CalculateLocation,FRotator* CalculateRotation,float* CalculateFOV);
	virtual void UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime) override;

	
private:
	void UpdateCharacterInfo();
	FVector CalculateAxisIndependentLag(FVector CurrentLocation,FVector TargetLocation,FRotator CameraRotation,FVector LagSpeeds) const;

public:
	UFUNCTION(BlueprintNativeEvent,Category = "CameraParamet")
	void GetCameraParamet();
	//void GetCameraParamet_Implementation();
	
};
// PlayerCamera-End 2025/10/20