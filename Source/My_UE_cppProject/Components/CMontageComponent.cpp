// Fill out your copyright notice in the Description page of Project Settings.


#include "CMontageComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UCMontageComponent::UCMontageComponent()
{

	// ...
}


// Called when the game starts
void UCMontageComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable == nullptr)
	{
		CLog::Log("DataTable is not found in" + GetOwner()->GetName());
		CLog::Print("DataTable is not found in" + GetOwner()->GetName());
		return;
	}
		CLog::Print("Data");

	TArray<FMontageData*> datas;
	DataTable->GetAllRows<FMontageData>("", datas);

	for (int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		CLog::Print("Data");
		for (FMontageData* data : datas)
		{
			CLog::Print(data->AnimMontage->GetName() + ", " + FString::SanitizeFloat(data->PlayRate));
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;
				continue;
				CLog::Print(data->AnimMontage->GetName() + ", " + FString::SanitizeFloat(data->PlayRate));
			}
		}
	}
	
}

void UCMontageComponent::PlayRoll()
{
	PlayAnimMontage(EStateType::Roll);
}

void UCMontageComponent::PlayHitted()
{
	PlayAnimMontage(EStateType::Hitted);
}

void UCMontageComponent::PlayDead()
{
}

void UCMontageComponent::PlayAnimMontage(EStateType InType)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	CheckNull(character);

	const FMontageData* data = Datas[(int32)InType];

	if (!!data)
	{
		if (!!data->AnimMontage)
			character->PlayAnimMontage(data->AnimMontage, data->PlayRate, data->StartSection);
	}
	//CLog::Print(data->AnimMontage->GetName() + ", " + FString::SanitizeFloat(data->PlayRate));
}


