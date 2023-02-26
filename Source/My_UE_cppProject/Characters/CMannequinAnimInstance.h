#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CMannequinAnimInstance.generated.h"

UCLASS()
class MY_UE_CPPPROJECT_API UCMannequinAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bIsFalling;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bIsCrouching;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
