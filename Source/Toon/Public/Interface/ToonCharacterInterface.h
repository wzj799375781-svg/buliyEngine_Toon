// buliy
//LocomotionSystem-Begin 3
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToonCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,Blueprintable)
class UToonCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOON_API IToonCharacterInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CharacterInformation")
	void GetEssentialValues(FVector& Velocity,FVector& Accele,FVector& MovementInput,bool& IsMoving,bool& HasMovementInput
		,float& Speed,float& MovementInputAmount,FRotator& AimingRotation,float& AimYawRate);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CharacterInformation")
	void GetCurrentStates(TEnumAsByte<EMovementMode>& PawnMovementMode, EMovementState& MovementState, EMovementState& PrevMovementState, ERotationMode& RotationMode
		, EGait& ActualGait, EStance& ActualStance, EOverlayState& OverlayState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character States")
	void SetMovementState(EMovementState NewMovementState);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character States")
	void SetRotationMode(ERotationMode NewRotationMode);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character States")
	void SetGait(EGait NewGait);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character States")
	void SetOverlayState(EOverlayState NewOverlayState);

};
// LocomotionSystem-End 2025/10/20