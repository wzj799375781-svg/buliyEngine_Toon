// buliy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ToonCharacterBase.generated.h"

UCLASS(Abstract)
class TOON_API AToonCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	
	AToonCharacterBase();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
};
