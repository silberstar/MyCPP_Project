#pragma once

#include "CoreMinimal.h"
#include "CCharacter.h"
#include "Components/CStateComponent.h"
#include "CPlayer.generated.h"

UCLASS()
class MY_UE_CPPPROJECT_API ACPlayer : public ACCharacter
{
	GENERATED_BODY()

	ACPlayer();

private: // ¾À ÄÄÆ÷³ÍÆ®
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private://¾×ÅÍ ÄÄÆ÷³ÍÆ®
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontageComponent* Montage;

protected:
	virtual void BeginPlay() override;

private:
	void OnMoveForward(		float InAxis);
	void OnMoveRight(		float InAxis);
	void OnHorizontalLook(	float InAxis);
	void OnVerticalLook(	float InAxis);
	void OnZoom(			float InAxis);

	void OnJump();
	void OnCrouch();
	void OnEvade();
	void OnAction();
	void OnSkill_01();
	void OnSkill_02();
	void OnSkill_03();
	void OnSkill_04();
	void OnSkill_05();

	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Begin_Roll();
	void End_Roll();

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

	
};
