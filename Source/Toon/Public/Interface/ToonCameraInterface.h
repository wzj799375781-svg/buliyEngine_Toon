// buliy
// PlayerCamera-Begin 1


#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToonCameraInterface.generated.h"
	
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UToonCameraInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOON_API IToonCameraInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.、
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CameraSystem")
	void GetCameraParameters(float& TP_FOV, bool& RightShoulder);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CameraSystem")
	void Get3PPivotTarget(FTransform& OutTransform);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CameraSystem")
	void Get3PTraceParams(FVector& TraceOrigin, float& TraceRadius, TEnumAsByte<ETraceTypeQuery>& TraceChannel);
};
// PlayerCamera-End 2025/10/20