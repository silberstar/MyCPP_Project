// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "C_Vege_Corn.generated.h"

UCLASS()
class MY_UE_CPPPROJECT_API AC_Vege_Corn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Vege_Corn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* SkeletalMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		TArray<UStaticMeshComponent*> SpawnFruit(FName SocketName, UStaticMesh* StaticMesh1, FVector RelativeScale1, UStaticMesh* StaticMesh2, FVector RelativeScale2);


private:
	USceneComponent* DefaultSceneRoot;

};
