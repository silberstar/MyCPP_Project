#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Sneak, Walk, Run, Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MY_UE_CPPPROJECT_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCStatusComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetSneakSpeed()	{ return Speed[(int32)ESpeedType::Sneak];	}
	FORCEINLINE float GetWalkSpeed()	{ return Speed[(int32)ESpeedType::Walk];	}
	FORCEINLINE float GetRunSpeed()		{ return Speed[(int32)ESpeedType::Run];		}
	FORCEINLINE bool IsCanMove()		{ return bCanMove;							}

	void SetMove();
	void SetStop();

	void SetSpeed(ESpeedType InType);

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float Speed[(int32)ESpeedType::Max] = { 200, 400, 600 };
private:
	bool bCanMove = true;
};
