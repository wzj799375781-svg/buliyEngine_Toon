// buliy

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/Locomotion/ToonLocomotionData.h"
#include "ToonAnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TOON_API UToonAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<ACharacter> ToonCharacter;
	

	

public:
	void NativeInitializeAnimation() override;
	
};
