// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CRollAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class MY_UE_CPPPROJECT_API UCRollAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

		FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
};
