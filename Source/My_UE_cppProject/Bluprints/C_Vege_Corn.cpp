#include "C_Vege_Corn.h"
#include "../Global.h"

AC_Vege_Corn::AC_Vege_Corn()
{
	PrimaryActorTick.bCanEverTick = true;

    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    RootComponent = DefaultSceneRoot;
    
    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyActor", meta = (AllowPrivateAccess = "true"))
    //    USkeletalMeshComponent* SkeletalMesh;
    
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMesh->SetupAttachment(DefaultSceneRoot);


}

void AC_Vege_Corn::BeginPlay()
{
	Super::BeginPlay();

    SkeletalMesh->SetRelativeScale3D(FVector(0.01f, 0.01f, 0.01f));
	
}

void AC_Vege_Corn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<UStaticMeshComponent*> AC_Vege_Corn::SpawnFruit(FName SocketName, UStaticMesh* StaticMesh1, FVector RelativeScale1, UStaticMesh* StaticMesh2, FVector RelativeScale2)
{
    TArray<UStaticMeshComponent*> SpawnedComponents;
   
    // SocketName이 유효한지 검사합니다.
    if (!SkeletalMesh->DoesSocketExist(SocketName))
    {
        UE_LOG(LogTemp, Error, TEXT("Socket %s does not exist in SkeletalMesh"), *SocketName.ToString());
        return SpawnedComponents;
    }
   
    // Socket 위치에 첫 번째 StaticMeshComponent를 생성합니다.
    UStaticMeshComponent* StaticMeshComp1 = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
    StaticMeshComp1->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
   
    // 첫 번째 UStaticMeshComponent의 StaticMesh 속성을 설정합니다.
    if (StaticMesh1)
    {
        StaticMeshComp1->SetStaticMesh(StaticMesh1);
    }
   
    // 첫 번째 UStaticMeshComponent의 상대적 크기를 설정합니다.
    StaticMeshComp1->SetRelativeScale3D(RelativeScale1);
   
    // Socket 위치에 두 번째 StaticMeshComponent를 생성합니다.
    UStaticMeshComponent* StaticMeshComp2 = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
    StaticMeshComp2->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
   
    // 두 번째 UStaticMeshComponent의 StaticMesh 속성을 설정합니다.
    if (StaticMesh2)
    {
        StaticMeshComp2->SetStaticMesh(StaticMesh2);
    }
   
    // 두 번째 UStaticMeshComponent의 상대적 크기를 설정합니다.
    StaticMeshComp2->SetRelativeScale3D(RelativeScale2);
   
    SpawnedComponents.Add(StaticMeshComp1);
    SpawnedComponents.Add(StaticMeshComp2);
   
    return SpawnedComponents;



}

