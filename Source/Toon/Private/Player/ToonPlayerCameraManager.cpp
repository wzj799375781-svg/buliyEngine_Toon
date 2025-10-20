// buliy


#include "Player/ToonPlayerCameraManager.h"
#include "Interface/ToonCameraInterface.h"
#include "Interface/ToonCharacterInterface.h"
#include "Kismet/KismetSystemLibrary.h"

AToonPlayerCameraManager::AToonPlayerCameraManager()
{
	

}


void AToonPlayerCameraManager::OnPossess(APawn* NewPawn)
{
	ControlledPawn = NewPawn;
	
}

void AToonPlayerCameraManager::CustomCameraBehavior(FVector* CalculateLocation, FRotator* CalculateRotation,
	float* CalculateFOV)
{
	//TODO:将CharacterBP替换成表内数据
	//1.通过相机接口从CharacterBP获取相机参数
	if (ControlledPawn->GetClass()->ImplementsInterface(UToonCameraInterface::StaticClass())) {
		
		IToonCameraInterface::Execute_Get3PPivotTarget(ControlledPawn, PivotTarget);
		bool DummyValue;
		IToonCameraInterface::Execute_GetCameraParameters(ControlledPawn, TPFOV, DummyValue);
	}
	/*-------------------------------*/

	//2.设置不同视角值
	GetCameraParamet();
	//3.计算目标相机旋转，使用旋转控制和插值平滑相机旋转。
	TargetCameraRotation = FMath::RInterpTo(GetCameraRotation(), GetOwningPlayerController()->GetControlRotation(), GetWorld()->GetDeltaSeconds(), RotationLagSpeed);

	//4.计算平滑枢轴目标（SmoothPivotTarget），获得3P枢轴目标(GetCameraBehaviorPararm)，并使用XYZ轴独立延迟进行插值，以获得最大的控制实现丝滑过度。
	auto newVector = CalculateAxisIndependentLag(SmoothedPivotTarget.GetLocation(), PivotTarget.GetLocation(), TargetCameraRotation, FVector(PivotLagSpeed_X, PivotLagSpeed_Y, PivotLagSpeed_Z));
	SmoothedPivotTarget = FTransform(PivotTarget.GetRotation(), newVector, FVector(1.0f, 1.0f, 1.0f));

	//5.计算枢轴位置，获得平滑枢轴目标，并应用本地偏移将默认在角色胯部下的枢纽点大致在角色的腹部位置
	PivotLocation = SmoothedPivotTarget.GetLocation() + SmoothedPivotTarget.GetRotation().GetForwardVector() * PivotOffset_X + 
		SmoothedPivotTarget.GetRotation().GetRightVector() * PivotOffset_Y +
		SmoothedPivotTarget.GetRotation().GetUpVector() * PivotOffset_Z;

	//6. 计算目标相机位，获得枢纽位置并应用相机相对偏移量
	TargetCameraLocation=PivotLocation+TargetCameraRotation.Quaternion().GetForwardVector()* CameraOffset_X+
	TargetCameraRotation.Quaternion().GetRightVector()* CameraOffset_Y+
	TargetCameraRotation.Quaternion().GetUpVector()* CameraOffset_Z;
	

	//7.跟踪相机和角色之间的对象，纠正偏移量，轨迹远点是通过角色接口BP中设置的，（功能像是普通的弹簧臂，但可以不同的检测原点，而不是像默认弹簧臂只是一条射线检测
	if (ControlledPawn->GetClass()->ImplementsInterface(UToonCameraInterface::StaticClass()))
	{
		FVector TraceOrigin;
		float TraceRadius;
		TEnumAsByte<ETraceTypeQuery> TraceChannel;
		IToonCameraInterface::Execute_Get3PTraceParams(ControlledPawn,TraceOrigin, TraceRadius,TraceChannel);

		FHitResult HitResult;
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(ControlledPawn);
		bool bHit = UKismetSystemLibrary::SphereTraceSingle(
			GetWorld(),
			TraceOrigin,
			TargetCameraLocation,
			TraceRadius,
			TraceChannel,
			false,
			ActorsToIgnore,
			EDrawDebugTrace::None,
			HitResult,
			true
		);
		if (HitResult.bBlockingHit &&!HitResult.bStartPenetrating) {
			TargetCameraLocation = HitResult.Location - HitResult.TraceEnd + TargetCameraLocation;
			
		}
	}

	//8.返回参数
	*CalculateLocation = TargetCameraLocation;
	*CalculateRotation = TargetCameraRotation;
	*CalculateFOV     = TPFOV;
	
}

void AToonPlayerCameraManager::UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime)
{
	
	Super::UpdateViewTargetInternal(OutVT, DeltaTime);

	UpdateCharacterInfo();

	if (!OutVT.Target)
	{
		return;
	}
	if (OutVT.Target->ActorHasTag("Player")) 
	{
		FVector CalculatedLocation;
		FRotator CalculatedRotation;
		float CalculatedFOV;

		CustomCameraBehavior(&CalculatedLocation, &CalculatedRotation,&CalculatedFOV);
		
	
		OutVT.POV.Location=CalculatedLocation;
		OutVT.POV.Rotation = CalculatedRotation;
		OutVT.POV.FOV = CalculatedFOV;
		
	}
	else
	{
		OutVT.Target->CalcCamera(DeltaTime, OutVT.POV);
	}
}


void AToonPlayerCameraManager::UpdateCharacterInfo()
{
	if (ControlledPawn && ControlledPawn->GetClass()->ImplementsInterface(UToonCharacterInterface::StaticClass())) {
		TEnumAsByte<EMovementMode> PawnMovementMode;
		EMovementState PrevMovementState;
		EOverlayState overlayState;
		IToonCharacterInterface::Execute_GetCurrentStates(ControlledPawn,PawnMovementMode, MovmentState, PrevMovementState, RotationMode, Gait,
												  Stance,overlayState);
	}
	if (ControlledPawn &&  ControlledPawn->GetClass()->ImplementsInterface(UToonCameraInterface::StaticClass()))
	{
		float TP_FOV;
		IToonCameraInterface::Execute_GetCameraParameters(ControlledPawn,TP_FOV,rightShoulder);
	}
}

FVector AToonPlayerCameraManager::CalculateAxisIndependentLag(FVector CurrentLocation, FVector TargetLocation,
                                                              FRotator CameraRotation, FVector LagSpeeds) const 
{
	FRotator CameraRotationYaw = FRotator(0, TargetCameraRotation.Yaw,0);

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	auto x=FMath::FInterpTo(CameraRotationYaw.UnrotateVector(CurrentLocation).X, CameraRotationYaw.UnrotateVector(TargetLocation).X, DeltaTime, LagSpeeds.X);
	auto y=FMath::FInterpTo(CameraRotationYaw.UnrotateVector(CurrentLocation).Y, CameraRotationYaw.UnrotateVector(TargetLocation).Y, DeltaTime, LagSpeeds.Y);
	auto z=FMath::FInterpTo(CameraRotationYaw.UnrotateVector(CurrentLocation).Z, CameraRotationYaw.UnrotateVector(TargetLocation).Z, DeltaTime, LagSpeeds.Z);
	return CameraRotationYaw.RotateVector(FVector(x, y, z));
}

void AToonPlayerCameraManager::GetCameraParamet_Implementation()
{
	
}


// PlayerCamera-End 2025/10/20
