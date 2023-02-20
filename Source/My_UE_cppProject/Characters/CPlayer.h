#pragma once

#include "CoreMinimal.h"
#include "CCharacter.h"
#include "CPlayer.generated.h"

UCLASS()
class MY_UE_CPPPROJECT_API ACPlayer : public ACCharacter
{
	GENERATED_BODY()

	ACPlayer();

private: // �� ������Ʈ
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private://���� ������Ʈ
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

protected:
	virtual void BeginPlay() override;

private:
	void OnMoveForward(		float InAxis);
	void OnMoveRight(		float InAxis);
	void OnHorizontalLook(	float InAxis);
	void OnVerticalLook(	float InAxis);
	void OnZoom(			float InAxis);

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

	
};