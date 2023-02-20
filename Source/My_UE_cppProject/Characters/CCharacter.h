#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "CCharacter.generated.h"

UCLASS()
class MY_UE_CPPPROJECT_API ACCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:	
	ACCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	 //class UMaterialInstanceDynamic* BodyMaterial;
	 //class UMaterialInstanceDynamic* LogoMaterial;

};
