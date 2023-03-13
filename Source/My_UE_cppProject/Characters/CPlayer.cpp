#include "CPlayer.h"
#include "../Global.h"

#include "GameFrameWork/SpringArmComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"

#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CMontageComponent.h"

#include "Camera/CameraComponent.h"

#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//Create SceneComponent
	CHelpers::CreateSceneComponent(this, &SpringArm	, "SpringArm"	, GetMesh());
	CHelpers::CreateSceneComponent(this, &Camera	, "Camera"		, SpringArm);

	//Create ActorComponent
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Option, "Option");
	CHelpers::CreateActorComponent(this, &Montage, "Montages");

	//ComponentSetting
	GetMesh()->SetRelativeLocation(FVector	(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator	(0, -90, 0));

	USkeletalMesh* meshAsset;
	CHelpers::GetAsset<USkeletalMesh>(&meshAsset, "/Game/Characters/Mesh/SK_Mannequin");
	GetMesh()->SetSkeletalMesh(meshAsset);

	TSubclassOf<UAnimInstance> animInstanceClass;
	CHelpers::GetClass<UAnimInstance>(&animInstanceClass, "/Game/Player/ABP_CMannequin");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);

	SpringArm->SetRelativeLocation(FVector	(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator	(0, 0, 0));
	SpringArm->SocketOffset.Z = 140;
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	Camera->SetRelativeRotation(FRotator(-45, 0, 0));


	//MovementSetting
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = Status->GetRunSpeed();
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Create Dynmaic Material
	UMaterialInstanceConstant* bodymaterial;
	UMaterialInstanceConstant* logomaterial;

	CHelpers::GetAssetDynamic(&bodymaterial, "/Game/Characters/Materials/M_UE4Man_Body_Inst"		);
	CHelpers::GetAssetDynamic(&logomaterial, "/Game/Characters/Materials/M_UE4Man_ChestLogo_Inst"	);

	BodyMaterial = UMaterialInstanceDynamic::Create(bodymaterial, nullptr);
	LogoMaterial = UMaterialInstanceDynamic::Create(logomaterial, nullptr);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	State->OnStateTypeChanged.AddDynamic(this, &ACPlayer::OnStateTypeChanged);

}

void ACPlayer::OnMoveForward(float InAxis)
{
	CheckFalse(Status->IsCanMove());
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnMoveRight(float InAxis)
{
	CheckFalse(Status->IsCanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	float rate = Option->GetHorizontalLookRate();
	AddControllerYawInput(	InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnVerticalLook(float InAxis)
{
	float rate = Option->GetVerticalLookRate();
	AddControllerPitchInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnZoom(float InAxis)
{
	SpringArm->TargetArmLength += Option->GetZoomSpeed() * InAxis * GetWorld()->GetDeltaSeconds();
	SpringArm->SocketOffset.Z += Option->GetZoomSpeed() * InAxis * GetWorld()->GetDeltaSeconds();
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, Option->GetZoomRange().X, Option->GetZoomRange().Y);
}

void ACPlayer::OnJump()
{
	Jump();
}

void ACPlayer::OnCrouch()
{
	Crouch();
}

void ACPlayer::OnEvade()
{
	CheckFalse(State->IsIdleMode());
	CheckFalse(Status->IsCanMove());

	//CLog::Print("Roll");

	State->SetRollMode();
}

void ACPlayer::OnAction()
{
}

void ACPlayer::OnSkill_01()
{
}

void ACPlayer::OnSkill_02()
{
}

void ACPlayer::OnSkill_03()
{
}

void ACPlayer::OnSkill_04()
{
}

void ACPlayer::OnSkill_05()
{
}

void ACPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Roll:		Begin_Roll();		break;
	}
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",	 this, &ACPlayer::OnMoveForward		);
	PlayerInputComponent->BindAxis("MoveRight",		 this, &ACPlayer::OnMoveRight		);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook	);
	PlayerInputComponent->BindAxis("VerticalLook",	 this, &ACPlayer::OnVerticalLook	);
	PlayerInputComponent->BindAxis("Zoom",			 this, &ACPlayer::OnZoom			);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACPlayer::OnJump);
	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &ACPlayer::OnCrouch);
	PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Pressed, this, &ACPlayer::OnEvade);
}

void ACPlayer::Begin_Roll()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	FVector start = GetActorLocation();
	FVector target = start + GetVelocity().GetSafeNormal2D();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target));

	Montage->PlayRoll();
}

void ACPlayer::End_Roll()
{
	State->SetIdleMode();
}

