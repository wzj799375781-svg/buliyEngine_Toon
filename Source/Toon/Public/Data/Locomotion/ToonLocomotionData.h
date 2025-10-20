//buliy
//LocomotionSystem-Begin 1
//Locomotion数据

#pragma once

#include "CoreMinimal.h"
#include "ToonLocomotionData.generated.h"


class UCurveFloat;
class UCurveVector;

//走跑冲刺
UENUM(BlueprintType)
enum class EGait :uint8 
{
	Walking,
	Running,
	Sprinting
};

//可扩展飞翔等状态
UENUM(BlueprintType)
enum class EMovementState :uint8
{
	None,
	Grounded,
};

//可扩展多武器状态
UENUM(BlueprintType)
enum class EOverlayState :uint8
{
	Default,
	Sword,
	Wand
};

UENUM(BlueprintType)
enum class ERotationMode :uint8
{
	VelocityDirection,
	LookingDirection,
	Aiming
};


//可扩展蹲伏状态
UENUM(BlueprintType)
enum class EStance :uint8
{
	Standing
};

UENUM(BlueprintType)
enum class EMovementDirection:uint8
{
	Forward,
	Right,
	Left,
	Backward
};

UENUM(BlueprintType)
enum class EHipsDirection:uint8
{
	F,
	B,
	RF,
	RB,
	LF,
	LB
};


USTRUCT(BlueprintType)
struct FMovementSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunSpeed=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SprintSpeed=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveVector* MovementCurve = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* RotationRateCurve=nullptr;
};

USTRUCT(BlueprintType)
struct FMovementSettingsStance
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMovementSettings Standing= FMovementSettings();
};

USTRUCT(BlueprintType)
struct FMovementSettingsState :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMovementSettingsStance VelocityDirection = FMovementSettingsStance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMovementSettingsStance LookingDirection = FMovementSettingsStance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMovementSettingsStance Aiming = FMovementSettingsStance();
};


//速度方向移动
USTRUCT(BlueprintType)
struct FVelocityBlend
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float F = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float B = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float L = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float R = 0;
	FVelocityBlend() {}
	FVelocityBlend(float a, float b, float c, float d)
	{
		F = a;
		B = b;
		L = c;
		R = d;
	}
};

USTRUCT(BlueprintType)
struct FLeanAmount
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LR = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FB = 0;
	FLeanAmount() {}
	FLeanAmount(float lr, float fb)
	{
		LR = lr;
		FB = fb;

	}
};

//自动旋转
USTRUCT(BlueprintType)
struct FTurnInPlace_Asset 
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimSequence* Animation=nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AnimatedAngle=0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SlotName=FName();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayRate=0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ScaleTurnAngle=false;
};

//播放旋转蒙太奇
USTRUCT(BlueprintType)
struct FDynamicMontageParams
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimSequence* Animation=nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlendInTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlendOutTime=0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayRate = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartTime = 0;
};



//LocomotionSystem-End 2025/10/20