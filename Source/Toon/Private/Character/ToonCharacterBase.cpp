// buliy


#include "Character/ToonCharacterBase.h"


AToonCharacterBase::AToonCharacterBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	Weapon =CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}


void AToonCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}



