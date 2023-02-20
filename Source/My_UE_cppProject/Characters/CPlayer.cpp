#include "CPlayer.h"
#include "../Global.h"

#include "GameFrameWork/SpringArmComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"

#include "Components/CStatusComponent.h"
#include "Components/COptionComponent.h"

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
	CHelpers::CreateActorComponent(this, &Option, "Option");

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
	SpringArm->SetRelativeRotation(FRotator	(0, 90, 0));
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

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

	//MovementSetting
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = Status->GetRunSpeed();
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;
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
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, Option->GetZoomRange().X, Option->GetZoomRange().Y);
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
}