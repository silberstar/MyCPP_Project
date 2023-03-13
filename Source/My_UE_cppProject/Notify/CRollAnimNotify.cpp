// Fill out your copyright notice in the Description page of Project Settings.


#include "CRollAnimNotify.h"
#include "../Global.h"
#include "Characters/CPlayer.h"

FString UCRollAnimNotify::GetNotifyName_Implementation() const
{
	return "Rolled";
}

void UCRollAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	player->End_Roll();
}
