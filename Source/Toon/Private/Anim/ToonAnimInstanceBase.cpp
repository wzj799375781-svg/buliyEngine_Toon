// buliy


#include "Anim/ToonAnimInstanceBase.h"

#include "GameFramework/Character.h"

void UToonAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner()))
	{
		ToonCharacter = Character;
	}
}
