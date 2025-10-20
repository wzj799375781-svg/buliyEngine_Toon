// buliy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class TOON_API AToonPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	AToonPlayerController();
public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere,Category ="Input")
	TObjectPtr<UInputMappingContext> ToonContext;

	UPROPERTY(EditAnywhere,Category ="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const  FInputActionValue& InputActionValue);
};
